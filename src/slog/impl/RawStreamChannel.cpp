#include <slog/impl/RawStreamChannel.h>
#include <slog/ChannelFactory.h>
#include <iostream>
#include <chrono>
#include <iomanip>
#include <thread>
#include <unistd.h>
#include <sys/syscall.h>

namespace slog::impl
{

RawStreamChannel::RawStreamChannel( ChannelFactory & factory, const std::string & id, std::ostream & out, std::ostream & err, std::mutex & mtx, const Options & options ):
    Channel( factory, id, options.get<Level>( OPT_LOG_LEVEL, Level::INFO ) ),
    _out{ out },
    _err{ err },
    _mtx{ mtx },
    _syncRecord{ *this, nullptr },
    _recUnlocker{ _mtx },
    _async{ options.get<bool>( OPT_ASYNC, false ) },
    _logChannelName{ options.get<bool>( OPT_LOG_CHANNEL_NAME, false ) },
    _logThreadId{ options.get<bool>( OPT_LOG_THREAD_PID, false ) }
{
    int poolSize = options.get<int>( OPT_INITIAL_RECORD_POOL_SIZE, 10 );
    for( int i = 0; i < poolSize; ++i )
    {
        recycleRecord( new RawRecord( *this, nullptr ) );
    }
}

RawStreamChannel::~RawStreamChannel() 
{
}

Record::Ptr RawStreamChannel::createRecord( const Format * fmt )
{
    int tid = _logThreadId ? syscall(SYS_gettid) : 0;

    if( _async )
    {
        RawRecord::Ptr rec = popOrCreateRecord( fmt );
        rec->setThreadId( tid );
        rec->prepare();
        return rec;
    }
    else
    {
        RawRecord * rec = & _syncRecord;
        _mtx.lock();
        rec->setThreadId( tid );
        rec->setFormat( fmt );
        auto & s = fmt and isLevelReached( Level::WARNING,  fmt->getLevel() ) ? _err : _out; 
        saveFormat( s, fmt );
        insertLogPrefix( s, *rec );
        rec->prepare();
        return Record::Ptr( rec, _recUnlocker );
    }
}

void RawStreamChannel::writeRecord( Record::Ptr rec )
{
    if( _async )
    {
        getFactory().queueRecord( rec );
    }
    else
    {
        RawRecord * srec = static_cast< RawRecord * >( rec.get() );
        const Format * fmt = rec->getFormat();
        auto & s = fmt and isLevelReached( Level::WARNING,  fmt->getLevel() ) ? _err : _out; 
        srec->toAscii( s );
        s << std::endl;
    }
}

void RawStreamChannel::asyncWriteRecord( Record::Ptr rec )
{
    const Format * fmt = rec->getFormat();
    Level lvl = fmt ? fmt->getLevel() : getLoglevel();
    RawRecord * srec = static_cast< RawRecord * >( rec.get() );
    {
        auto & s = fmt and isLevelReached( Level::WARNING,  fmt->getLevel() ) ? _err : _out; 
        saveFormat( s, fmt );
        std::scoped_lock< std::mutex > protectStream( _mtx );
        insertLogPrefix( s, *srec );
        srec->toAscii( s );
        s << std::endl;
    }
    //std::this_thread::sleep_for( std::chrono::microseconds(1) );
}

void RawStreamChannel::insertLogPrefix( std::ostream & os, RawRecord & rec )
{
    const auto now = std::chrono::system_clock::now();
    const std::time_t t_c = std::chrono::system_clock::to_time_t(now);
    auto usecs = std::chrono::duration_cast<std::chrono::microseconds>(now.time_since_epoch()).count() % 1000000LU;
    const Format * fmt = rec.getFormat();
    Level lvl = fmt ? fmt->getLevel() : getLoglevel();
    os << '\1' << slog::to_char( lvl ) << ' ';
    os << std::put_time(std::localtime(&t_c), "%F %T.") << std::setfill('0') << std::setw(6) << usecs;
    if( _logThreadId )
    {
        os << ' ' << std::setfill(' ') << std::setw(5) << rec.getThreadId();
    }
    if( _logChannelName )
    {
        os << ' ' << getId() << ' ';
    }
    const char * id = fmt->getId().data();
    if( id[0] ) os << id[0];
    if( id[1] ) os << id[1];
    os << "\2 ";
}

RawRecord * RawStreamChannel::newRecord( const Format * fmt )
{
    return new RawRecord( *this, fmt );
}

bool RawStreamChannel::saveFormat( std::ostream & os, const Format * fmt )
{
    if( _knownFormats.insert( fmt->getId() ).second )
    {
        os << "\1F " << getId() << ' ';
        const char * id = fmt->getId().data();
        if( id[0] ) os << id[0];
        if( id[1] ) os << id[1];
        os << ' ';
        os << ( fmt->getMessageString() ? fmt->getMessageString() : "" ) << std::endl;
        return true;
    }
    return false;
}

}

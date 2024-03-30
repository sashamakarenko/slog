#include <slog/impl/StreamChannel.h>
#include <slog/ChannelFactory.h>
#include <iostream>
#include <chrono>
#include <iomanip>
#include <thread>

#include <unistd.h>
#include <sys/syscall.h>

namespace slog::impl
{

StreamChannel::StreamChannel( ChannelFactory & factory, const std::string & id, std::ostream & out, std::ostream & err, std::mutex & mtx, const Options & options )
: Channel( factory, id, options.get<Level>( OPT_LOG_LEVEL, Level::INFO ) )
, _async{ options.get<bool>( OPT_ASYNC, false ) }
, _logChannelName{ options.get<bool>( OPT_LOG_CHANNEL_NAME, false ) }
, _logThreadId{ options.get<bool>( OPT_LOG_THREAD_PID, false ) }
, _out{ out }
, _err{ err }
, _mtx{ mtx }
, _outSyncRecord{ *this, getFreeformFormat( Level::INFO  ), _out }
, _errSyncRecord{ *this, getFreeformFormat( Level::ERROR ), _err }
, _recUnlocker{ _mtx }
{
    int poolSize = options.get<int>( OPT_INITIAL_RECORD_POOL_SIZE, 10 );
    for( int i = 0; i < poolSize; ++i )
    {
        recycleRecord( new StrStreamRecord( *this, nullptr ) );
    }
}

StreamChannel::~StreamChannel()
{
}

Record::Ptr StreamChannel::createRecord( const Format * fmt )
{
    int tid = _logThreadId ? syscall(SYS_gettid) : 0;

    if( _async )
    {
        StreamRecord::Ptr rec = popOrCreateRecord( fmt );
        rec->setThreadId( tid );
        rec->prepare();
        return rec;
    }
    else
    {
        StreamRecord * rec = fmt and isLevelReached( Level::WARNING,  fmt->getLevel() ) ? & _errSyncRecord : & _outSyncRecord;
        _mtx.lock();
        rec->setThreadId( tid );
        rec->setFormat( fmt );
        insertLogPrefix( rec->getStream(), *rec );
        rec->prepare();
        return Record::Ptr( rec, _recUnlocker );
    }
}

void StreamChannel::writeRecord( Record::Ptr rec )
{
    if( _async )
    {
        getFactory().queueRecord( rec );
    }
    else
    {
        StreamRecord * srec = static_cast< StreamRecord * >( rec.get() );
        srec->getStream() << '\n';
        srec->flush();
    }
}

void StreamChannel::asyncWriteRecord( Record::Ptr rec )
{
    const Format * fmt = rec->getFormat();
    StrStreamRecord * srec = static_cast< StrStreamRecord * >( rec.get() );
    {
        auto & s = fmt and isLevelReached( Level::WARNING,  fmt->getLevel() ) ? _err : _out;
        std::scoped_lock< std::mutex > protectStream( _mtx );
        insertLogPrefix( s, *srec );
        s << srec->getString() << '\n';
        s.flush();
    }
    //std::this_thread::sleep_for( std::chrono::microseconds(1) );
}

void StreamChannel::insertLogPrefix( std::ostream & os, StreamRecord & rec )
{
    const auto now = std::chrono::system_clock::now();
    const std::time_t t_c = std::chrono::system_clock::to_time_t(now);
    auto usecs = std::chrono::duration_cast<std::chrono::microseconds>(now.time_since_epoch()).count() % 1000000LU;
    const Format * fmt = rec.getFormat();
    Level lvl = fmt ? fmt->getLevel() : getLoglevel();
    os << slog::to_char( lvl ) << ' ';
    os << std::put_time(std::localtime(&t_c), "%F %T.") << std::setfill('0') << std::setw(6) << usecs;
    if( _logThreadId )
    {
        os << " " << std::setfill(' ') << std::setw(5) << rec.getThreadId();
    }
    if( _logChannelName )
    {
        os << " " << getId() << ": ";
    }
}

StreamRecord * StreamChannel::newRecord( const Format * fmt )
{
    return new StrStreamRecord( *this, fmt );
}

}

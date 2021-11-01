#include <slog/impl/AsyncRecordQueue.h>
#include <slog/Channel.h>
#include <slog/Options.h>
#include <iostream>

namespace slog::impl
{

AsyncRecordQueue::AsyncRecordQueue( const Options & opts ):
    _threadName{ opts.get<std::string>( OPT_BG_THREAD_NAME, "logger" ).substr( 0, 15 ) },
    _keepRunning{ true },
    _sendAllOnExit{ opts.get<bool>( OPT_SEND_ALL_ON_EXIT, true ) }
{
    _thread = std::thread( &AsyncRecordQueue::bgLoop, this );
}

AsyncRecordQueue::~AsyncRecordQueue()
{
    {
        std::unique_lock<std::mutex> protectQueue( _queueGuard );
        _keepRunning = false;
    }
    _condvar.notify_all();
    _thread.join();
}

void AsyncRecordQueue::bgLoop()
{
    pthread_setname_np( pthread_self(), _threadName.c_str() );
    std::cout << "bg thread '" << _threadName << "' started\n";
    while( _keepRunning or ( _sendAllOnExit and not _queue.empty() ) )
    {
        Record::Ptr rec;
        {
            std::unique_lock<std::mutex> protectQueue( _queueGuard );
            while( _keepRunning && _queue.empty() )
            {
                _condvar.wait( protectQueue );
            }
            if( ( _keepRunning or _sendAllOnExit ) and not _queue.empty() )
            {
                rec = _queue.front();
                _queue.pop_front();
            }
        }
        if( rec )
        {
            rec->getChannel().asyncWriteRecord( rec );
        }
    }
    std::cout << "bg thread stopped\n";
}


long AsyncRecordQueue::queueRecord( Record::Ptr rec )
{
    std::unique_lock<std::mutex> protectQueue( _queueGuard );
    _queue.push_back( rec );
    _condvar.notify_one();
    return _queue.size();
}


}

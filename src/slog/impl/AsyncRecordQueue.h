#pragma once
#ifndef SLOG_ASYNC_RECORD_QUEUE_H
#define SLOG_ASYNC_RECORD_QUEUE_H

#include <slog/Record.h>
#include <deque>
#include <mutex>
#include <condition_variable>
#include <thread>

namespace slog
{
    class Options;
}
namespace slog::impl
{

class AsyncRecordQueue
{
    public:

        AsyncRecordQueue( const Options & opts );

        ~AsyncRecordQueue();

        long queueRecord( Record::Ptr rec );

    private:

        void bgLoop();
        
        std::mutex              _queueGuard;
        std::condition_variable _condvar;
        std::deque<Record::Ptr> _queue;
        std::thread             _thread;
        std::string             _threadName;
        bool volatile           _keepRunning;
        bool                    _sendAllOnExit;
};

}

#endif

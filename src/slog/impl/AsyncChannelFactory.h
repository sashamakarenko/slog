#pragma once
#ifndef SLOG_ASYNC_CHANNEL_FACTORY_H
#define SLOG_ASYNC_CHANNEL_FACTORY_H

#include <slog/ChannelFactory.h>
#include <slog/impl/AsyncRecordQueue.h>

namespace slog::impl
{

class AsyncChannelFactory: public ChannelFactory
{
    public:

        AsyncChannelFactory( const Options & opts );

        virtual long queueRecord( Record::Ptr rec ) override;

    private:

        AsyncRecordQueue _queue;
};

}

#endif

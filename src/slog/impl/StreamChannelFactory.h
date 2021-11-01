#pragma once
#ifndef SLOG_STREAM_CHANNEL_FACTORY_H
#define SLOG_STREAM_CHANNEL_FACTORY_H

#include <slog/impl/StreamChannel.h>
#include <slog/impl/AsyncChannelFactory.h>

namespace slog::impl
{

class StreamChannelFactory: public AsyncChannelFactory
{
    public:

        StreamChannelFactory( std::ostream & out, std::ostream & err, const Options & options = {} );

        explicit StreamChannelFactory( std::ostream & out, const Options & options = {} );

        virtual const std::string & getName() const override;

    protected:

        virtual Channel::Ptr createChannel( const std::string & id, const Options & options ) override;

        std::mutex & getMutex()
        {
            return _mtx;
        }

    private:

        std::ostream & _out;
        std::ostream & _err;
        std::mutex     _mtx;
};

}

#endif

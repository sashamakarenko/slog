#pragma once
#ifndef SLOG_TTY_CHANNEL_FACTORY_H
#define SLOG_TTY_CHANNEL_FACTORY_H

#include <slog/impl/StreamChannelFactory.h>

namespace slog::impl
{

class TtyChannelFactory: public StreamChannelFactory
{
    public:

        TtyChannelFactory( const Options & options = {} );

        virtual const std::string & getName() const override;

    protected:

        virtual Channel::Ptr createChannel( const std::string & id, const Options & options ) override;

};

}

#endif

#pragma once
#ifndef SLOG_TTY_STRSTREAM_CHANNEL_H
#define SLOG_TTY_STRSTREAM_CHANNEL_H

#include <slog/impl/StreamChannel.h>

namespace slog::impl
{

class TtyStreamChannel: public StreamChannel
{

    public:

        TtyStreamChannel( ChannelFactory & factory, const std::string & id, std::ostream & out, std::ostream & err, std::mutex & mtx, const Options & options );

        virtual ~TtyStreamChannel() override;

    protected:

        virtual void insertLogPrefix( std::ostream & os, StreamRecord & rec );

};

}

#endif

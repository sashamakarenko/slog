#pragma once
#ifndef SLOG_MESSAGE_H
#define SLOG_MESSAGE_H

#include <slog/Format.h>
#include <tuple>

namespace slog
{

template < const Format * Fmt, typename ...ArgTypes >
class Message
{
    public:

        using AllArgs = std::tuple<ArgTypes...>;

        static const Format * getFormat()
        {
            static_assert( Fmt != nullptr );
            return Fmt;
        }

        static Level getLevel()
        {
            return getFormat()->getLevel();
        }

        static const Format::Id & getId()
        {
            return getFormat()->getId();
        }

        static const char * getFormatString()
        {
            return getFormat()->getMessageString();
        }

        Message( const Message & ) = delete;
};

}

#endif

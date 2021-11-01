#pragma once
#ifndef SLOG_STRSTREAM_RECORD_H
#define SLOG_STRSTREAM_RECORD_H

#include <slog/impl/StreamRecord.h>
#include <sstream>

namespace slog::impl
{

class StrStreamRecord: public StreamRecord
{
    public:

        StrStreamRecord( Channel & channel, const Format * fmt ):
            StreamRecord( channel, fmt, _sstream )
        {
            _sstream << " Force preallocation of 512 bytes as per GCC implementation    ";
            reset();
        }

        virtual void reset() override
        {
            _sstream.str("");
        }

    private:

        friend class StreamChannel;

        std::string getString()
        {
            return _sstream.str();
        }

    private:

        std::ostringstream _sstream;
};

}

#endif

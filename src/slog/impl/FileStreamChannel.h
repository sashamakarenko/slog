#pragma once
#ifndef SLOG_FILE_STRSTREAM_CHANNEL_H
#define SLOG_FILE_STRSTREAM_CHANNEL_H

#include <slog/impl/StreamChannel.h>
#include <fstream>

namespace slog::impl
{

class FileStreamChannel: public StreamChannel
{

    public:

        FileStreamChannel( ChannelFactory & factory, const std::string & id, const std::string & path, const Options & options );

        virtual ~FileStreamChannel() override;

    protected:

    private:

        std::string   _path;
        std::ofstream _file;
        std::mutex    _mtx;
};

}

#endif

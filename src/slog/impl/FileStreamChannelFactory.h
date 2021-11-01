#pragma once
#ifndef SLOG_FILE_STREAM_CHANNEL_FACTORY_H
#define SLOG_FILE_STREAM_CHANNEL_FACTORY_H

#include <slog/impl/AsyncChannelFactory.h>
#include <fstream>

namespace slog::impl
{

class FileStreamChannelFactory: public AsyncChannelFactory
{
    public:

        explicit FileStreamChannelFactory( const std::string & path, const Options & options = {} );

        virtual const std::string & getName() const override;

        virtual ~FileStreamChannelFactory();

    protected:

        virtual Channel::Ptr createChannel( const std::string & id, const Options & options ) override;

    private:

        std::ofstream  _file;
        std::string    _path; 
        bool           _isMultiFile;
        std::mutex     _mtx;
};

}

#endif

#include <slog/impl/FileStreamChannel.h>

namespace slog::impl
{

FileStreamChannel::FileStreamChannel( ChannelFactory & factory, const std::string & id, const std::string & path, const Options & options ):
    StreamChannel( factory, id, _file, _file, _mtx, options ),
    _path{ path },
    _file{ path },
    _mtx{}
{
}

FileStreamChannel::~FileStreamChannel() 
{
    _file.close();
}

}

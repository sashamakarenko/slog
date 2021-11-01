
#include <slog/impl/FileStreamChannelFactory.h>
#include <slog/impl/FileStreamChannel.h>
#include <iostream>

namespace slog::impl
{

FileStreamChannelFactory::FileStreamChannelFactory( const std::string & path, const Options & options ):
    AsyncChannelFactory( options ),
    _file{},
    _path{ path },
    _isMultiFile{ options.get<bool>( OPT_MULTIFILE, true ) }
{
    if( not _isMultiFile )
    {
        _file.open( path );
    }
}

FileStreamChannelFactory::~FileStreamChannelFactory()
{
    if( not _isMultiFile )
    {
        _file.close();
    }
}

Channel::Ptr FileStreamChannelFactory::createChannel( const std::string & id, const Options & options )
{
    if( _isMultiFile )
    {
        return std::make_shared<FileStreamChannel>( *this, id, _path + "/" + id + ".log", options );
    }
    else
    {
        return std::make_shared<StreamChannel>( *this, id, _file, _file, _mtx, options );
    }
}

const std::string & FileStreamChannelFactory::getName() const
{
    static std::string name( "FileStreamChannelFactory" );
    return name;
}


}

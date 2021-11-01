
#include <slog/impl/TtyChannelFactory.h>
#include <slog/impl/TtyStreamChannel.h>
#include <iostream>

namespace slog::impl
{

TtyChannelFactory::TtyChannelFactory( const Options & options ):
    StreamChannelFactory( std::cout, std::cerr, options )
{
}


Channel::Ptr TtyChannelFactory::createChannel( const std::string & id, const Options & options )
{
    return std::make_shared<TtyStreamChannel>( *this, id, std::cout, std::cerr, getMutex(), options );
}
 
const std::string & TtyChannelFactory::getName() const
{
    static std::string name( "TtyChannelFactory" );
    return name;
}

}

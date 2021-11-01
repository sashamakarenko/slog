
#include <slog/impl/StreamChannelFactory.h>
#include <slog/impl/StreamChannel.h>
#include <slog/impl/RawStreamChannel.h>
#include <iostream>

namespace slog::impl
{

StreamChannelFactory::StreamChannelFactory( std::ostream & out, std::ostream & err, const Options & options ):
    AsyncChannelFactory( options ),
    _out{ out },
    _err{ err }
{
}

 StreamChannelFactory::StreamChannelFactory( std::ostream & out, const Options & options ):
    StreamChannelFactory( out, out, options )
{
}


Channel::Ptr StreamChannelFactory::createChannel( const std::string & id, const Options & options )
{
    if( options.get<bool>( OPT_USE_RAW_LOGGER, false ) ) 
    {
        return std::make_shared<RawStreamChannel>( *this, id, _out, _err, _mtx, options );
    }
    return std::make_shared<StreamChannel>( *this, id, _out, _err, _mtx, options );
}
 
const std::string & StreamChannelFactory::getName() const
{
    static std::string name( "StreamChannelFactory" );
    return name;
}

}

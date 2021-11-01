#include <slog/Channel.h>
#include <slog/ChannelFactory.h>

namespace slog
{

Channel::Channel( ChannelFactory & factory, const std::string & id, Level lvl ): 
    _factory{ factory },
    _id{ id },
    _level{ lvl } 
{

}

Channel::~Channel()
{

}

const Options EmptyOptions;

Channel & createChannel( const std::string & id, const Options & options )
{
    return ChannelFactory::getInstance()->getChannel( id, options );
}

void Channel::asyncWriteRecord( Record::Ptr rec )
{

}

namespace
{
    slog::Format FMT_UNKNOWN( slog::Level::ERROR  , "U", nullptr );
    slog::Format FMT_MUTE   ( slog::Level::MUTE   , "M", nullptr );
    slog::Format FMT_PANIC  ( slog::Level::PANIC  , "P", nullptr );
    slog::Format FMT_ERROR  ( slog::Level::ERROR  , "E", nullptr );
    slog::Format FMT_WARNING( slog::Level::WARNING, "W", nullptr );
    slog::Format FMT_INFO   ( slog::Level::INFO   , " ", nullptr );
    slog::Format FMT_DEBUG  ( slog::Level::DEBUG  , "D", nullptr );
    slog::Format FMT_TRACE  ( slog::Level::TRACE  , "T", nullptr );
}

const Format * Channel::getFreeformFormat( Level lvl )
{
    switch( lvl )
    {
        case slog::Level::MUTE:
            return &FMT_MUTE;
            
        case slog::Level::PANIC:
            return &FMT_PANIC;
            
        case slog::Level::ERROR:
            return &FMT_ERROR;
            
        case slog::Level::WARNING:
            return &FMT_WARNING;
            
        case slog::Level::INFO:
            return &FMT_INFO;
            
        case slog::Level::DEBUG:
            return &FMT_DEBUG;
            
        case slog::Level::TRACE:
            return &FMT_TRACE;

        default:
            return &FMT_UNKNOWN;            
    }
}


}
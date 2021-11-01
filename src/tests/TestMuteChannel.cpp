
#include <tests/Formats.h>
#include <slog/impl/MuteChannelFactory.h>

int main( int args, const char ** argv )
{
    slog::ChannelFactory::setInstance( new slog::impl::MuteChannelFactory() );
    slog::Channel & ch = slog::createChannel( "quiet" );
    logAllMessages( ch );
}

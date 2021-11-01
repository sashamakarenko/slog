
#include <tests/Formats.h>
#include <slog/impl/TtyChannelFactory.h>
#include <iostream>
#include <chrono>

int main( int args, const char ** argv )
{
    slog::ChannelFactory::setInstance( new slog::impl::TtyChannelFactory() );
    slog::Channel & ch1 = slog::createChannel( "std1", { { slog::OPT_ASYNC, true  }, { slog::OPT_LOG_CHANNEL_NAME, true }, { slog::OPT_LOG_THREAD_PID, true }, { slog::OPT_LOG_LEVEL, slog::Level::TRACE } } );
    slog::Channel & ch2 = slog::createChannel( "std2", { { slog::OPT_ASYNC, true  }, { slog::OPT_LOG_CHANNEL_NAME, true }, { slog::OPT_LOG_THREAD_PID, true }, { slog::OPT_LOG_LEVEL, slog::Level::DEBUG } } );
    slog::Channel & ch3 = slog::createChannel( "std3", { { slog::OPT_ASYNC, false }, { slog::OPT_LOG_CHANNEL_NAME, true }, { slog::OPT_LOG_THREAD_PID, true }, { slog::OPT_LOG_LEVEL, slog::Level::TRACE } } );
    logAllMessages( ch1 );
    logAllMessages( ch2 );
    logAllMessages( ch3 );
}

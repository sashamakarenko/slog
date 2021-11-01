
#include <tests/Formats.h>
#include <slog/impl/StreamChannelFactory.h>
#include <iostream>
#include <chrono>

int main( int args, const char ** argv )
{
    slog::ChannelFactory::setInstance( new slog::impl::StreamChannelFactory( std::cout, { { slog::OPT_BG_THREAD_NAME, "bg.logger" } } ) );
    slog::Channel & ch1 = slog::createChannel( "stda", { { slog::OPT_ASYNC, true  }, { slog::OPT_LOG_CHANNEL_NAME, true }, { slog::OPT_LOG_THREAD_PID, true }, { slog::OPT_INITIAL_RECORD_POOL_SIZE, 1 } } );
    slog::Channel & ch2 = slog::createChannel( "stds", { { slog::OPT_ASYNC, false }, { slog::OPT_LOG_CHANNEL_NAME, true }, { slog::OPT_LOG_THREAD_PID, true } } );
    slog::Channel & ch3 = slog::createChannel( "rawa", { { slog::OPT_ASYNC, true  }, { slog::OPT_LOG_CHANNEL_NAME, true }, { slog::OPT_LOG_THREAD_PID, true }, { slog::OPT_USE_RAW_LOGGER, true } } );
    slog::Channel & ch4 = slog::createChannel( "raws", { { slog::OPT_ASYNC, false }, { slog::OPT_LOG_CHANNEL_NAME, true }, { slog::OPT_LOG_THREAD_PID, true }, { slog::OPT_USE_RAW_LOGGER, true } } );
    logAllMessages( ch1 );
    logAllMessages( ch2 );
    logAllMessages( ch3 );
    logAllMessages( ch4 );
}


#include <tests/Formats.h>
#include <slog/impl/FileStreamChannelFactory.h>
#include <iostream>
#include <thread>
#include <chrono>

int main( int args, const char ** argv )
{
    slog::ChannelFactory::setInstance( new slog::impl::FileStreamChannelFactory( "out.log", { { slog::OPT_MULTIFILE, false } } ) );
    slog::Channel & ch1 = slog::createChannel( "std1", { { slog::OPT_ASYNC, true  }, { slog::OPT_LOG_CHANNEL_NAME, true }, { slog::OPT_LOG_THREAD_PID, true }, { slog::OPT_LOG_LEVEL, slog::Level::DEBUG } } );
    slog::Channel & ch2 = slog::createChannel( "std2", { { slog::OPT_ASYNC, true  }, { slog::OPT_LOG_CHANNEL_NAME, true }, { slog::OPT_LOG_THREAD_PID, true } } );
    slog::Channel & ch3 = slog::createChannel( "std3", { { slog::OPT_ASYNC, true }, { slog::OPT_LOG_CHANNEL_NAME, true }, { slog::OPT_LOG_THREAD_PID, true }, { slog::OPT_INITIAL_RECORD_POOL_SIZE, 1 } } );
    std::thread th1( [&]{ for( int i = 0; i < 100; ++i ) logAllMessages(ch1); } );
    std::thread th2( [&]{ for( int i = 0; i < 100; ++i ) logAllMessages(ch2); } );
    std::thread th3( [&]{ for( int i = 0; i < 100; ++i ) logAllMessages(ch3); } );
    th1.join();
    th2.join();
    th3.join();
}

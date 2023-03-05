#include <tests/Formats.h>
#include <chrono>
#include <thread>

slog::Format BadOrderFmt( slog::Level::ERROR, "BO", "Bad Order: qty=% px=%" );
slog::Format AllIntTypesFmt( slog::Level::DEBUG, "AI", "all int types: % % % % % % % %" );
slog::Format NoArgsMessageFmt( slog::Level::WARNING, "0A", "No args required" );
slog::Format ShowUserFmt( slog::Level::INFO, "SU", "User name=%" );
slog::Format ShowAccountFmt( slog::Level::INFO, "SA", "Account=%" );
slog::Format PermamemtCharPanicFmt( slog::Level::PANIC, "PP", "<%>" );

void logAllMessages( slog::Channel & channel )
{
    channel.log<ErrorBadOrder>( 10, 2.3 );
    std::this_thread::sleep_for(std::chrono::microseconds(11));

    channel.log<NoArgsMessage>();
    std::this_thread::sleep_for(std::chrono::microseconds(13));
    
    std::string user( "demo" );
    channel.log<ShowUser>( user.c_str() );
    std::this_thread::sleep_for(std::chrono::microseconds(17));

    const char * cptr = "AUser";
    channel.log<ShowUser>( cptr );
    std::this_thread::sleep_for(std::chrono::microseconds(19));

    std::string account = "AnAccount";
    channel.log<ShowAccount>( std::string_view( account ) );
    std::this_thread::sleep_for(std::chrono::microseconds(23));

    channel.log<AllIntTypes>( 'a', (short)16, 32, 64L, (unsigned char)'b', (unsigned short)17, 33U, 65UL );
    std::this_thread::sleep_for(std::chrono::microseconds(29));

    channel.log( slog::Level::ERROR, "unknown account:", (short)2, " acc", '1', " limited qty:", 10L, " bad px:", 1.23f );
    std::this_thread::sleep_for(std::chrono::microseconds(31));

    channel.trace( "this is a trace:", 10, " float:", 1.23f );

    channel.log<PermanentString>( "this is a pcp"_pcp );

    channel.debug( "free form:", 10, " float:", 1.23f );
    std::this_thread::sleep_for(std::chrono::microseconds(41));
}

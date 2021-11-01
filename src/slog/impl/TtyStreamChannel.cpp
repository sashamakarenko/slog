#include <slog/impl/TtyStreamChannel.h>
#include <chrono>
#include <iomanip>

namespace slog::impl
{

TtyStreamChannel::TtyStreamChannel( ChannelFactory & factory, const std::string & id, std::ostream & out, std::ostream & err, std::mutex & mtx, const Options & options ):
    StreamChannel( factory, id, out, err, mtx, options )
{
}

TtyStreamChannel::~TtyStreamChannel()
{

}

const char * ttyFg( slog::Level lvl )
{
    switch( lvl )
    {
        case slog::Level::MUTE:
            return "\e[35m";
           
        case slog::Level::PANIC:
            return "\e[91;1m";
            
        case slog::Level::ERROR:
            return "\e[31m";
            
        case slog::Level::WARNING:
            return "\e[93m";
            
        case slog::Level::INFO:
            return "\e[1m";
           
        case slog::Level::DEBUG:
            return "\e[37m";
            
        case slog::Level::TRACE:
            return "\e[37m";

        default:
            return "\e[33m";
    }
}

void TtyStreamChannel::insertLogPrefix( std::ostream & os, StreamRecord & rec )
{
    const auto now = std::chrono::system_clock::now();
    const std::time_t t_c = std::chrono::system_clock::to_time_t(now);
    auto usecs = std::chrono::duration_cast<std::chrono::microseconds>(now.time_since_epoch()).count() % 1000000LU;
    const Format * fmt = rec.getFormat();
    Level lvl = fmt ? fmt->getLevel() : getLoglevel();
    os << ttyFg(lvl) << slog::to_char( lvl ) << ' ';
    os << std::put_time(std::localtime(&t_c), "%T.") << std::setfill('0') << std::setw(6) << usecs<< "\e[0m";
    if( _logThreadId )
    {
        os << " \e[34m" << std::setfill(' ') << std::setw(5) << rec.getThreadId() << "\e[0m";
    }
    if( _logChannelName )
    {
        os << " \e[32m" << getId() << "\e[0m ";
    }

}

}


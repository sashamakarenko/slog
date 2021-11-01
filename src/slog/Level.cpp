#include <slog/Level.h>

namespace slog
{

namespace
{
    const std::string LVL_UNKNOWN[2] = { "UNKNOWN", "UNKNOWN" };
    const std::string LVL_MUTE   [2] = { "MUTE   ", "MUTE"    };
    const std::string LVL_PANIC  [2] = { "PANIC  ", "PANIC"   };
    const std::string LVL_ERROR  [2] = { "ERROR  ", "ERROR"   };
    const std::string LVL_WARNING[2] = { "WARNING", "WARNING" };
    const std::string LVL_INFO   [2] = { "INFO   ", "INFO"    };
    const std::string LVL_DEBUG  [2] = { "DEBUG  ", "DEBUG"   };
    const std::string LVL_TRACE  [2] = { "TRACE  ", "TRACE"   };
}

const std::string & to_string( slog::Level lvl, bool fixedWidth )
{
    const int offset = fixedWidth ? 1 : 0;
    switch( lvl )
    {
        case slog::Level::MUTE:
            return LVL_MUTE[offset];
           
        case slog::Level::PANIC:
            return LVL_PANIC[offset];
            
        case slog::Level::ERROR:
            return LVL_ERROR[offset];
            
        case slog::Level::WARNING:
            return LVL_WARNING[offset];
            
        case slog::Level::INFO:
            return LVL_INFO[offset];
           
        case slog::Level::DEBUG:
            return LVL_DEBUG[offset];
            
        case slog::Level::TRACE:
            return LVL_TRACE[offset];

        default:
            return LVL_UNKNOWN[offset];
    }
}

char to_char( slog::Level lvl )
{
    return to_string( lvl )[0];
}

}


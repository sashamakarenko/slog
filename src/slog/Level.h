#pragma once
#ifndef SLOG_LEVEL_H
#define SLOG_LEVEL_H

#include <string>
#include <iosfwd>

namespace slog
{

enum class Level: unsigned char
{
    MUTE    = 0,
    PANIC   = 4,
    ERROR   = 8,
    WARNING = 16,
    INFO    = 32,
    DEBUG   = 64,
    TRACE   = 128
};

const std::string & to_string( slog::Level lvl, bool fixedWidth = false );
char to_char( slog::Level lvl );

inline bool isLevelReached( Level treshold, Level lvl )
{
    return lvl > Level::MUTE && lvl <= treshold;
}

}

namespace std
{

inline const std::string & to_string( slog::Level lvl )
{
    return slog::to_string( lvl );
}

}

inline std::ostream & operator << ( std::ostream & os, const slog::Level & level )
{
    return os << slog::to_string( level );
}

#endif

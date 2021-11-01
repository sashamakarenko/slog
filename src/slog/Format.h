#pragma once
#ifndef SLOG_FORMAT_H
#define SLOG_FORMAT_H

#include <slog/Level.h>

namespace slog
{

class Format
{
    public:

        struct Id
        {
            typedef uint16_t ValueType;
            Id( const char * str ): value{ *reinterpret_cast< const ValueType * >( str ) } {}
            Id( ValueType v ): value{ v } {}
            const char * data() const { return reinterpret_cast< const char * >( &value ); }
            bool operator < ( const Id & other ) const { return value < other.value; }
            const ValueType value;
        };

        Format( Level level, const char * id, const char * fmt ): 
            _level{ level }, 
            _id{ id },
            _format{ fmt }
        {
        }

        Format( Level level, Id::ValueType id, const char * fmt ): 
            _level{ level }, 
            _id{ id },
            _format{ fmt }
        {
        }

        Level getLevel() const
        {
            return _level;
        }

        const Id & getId() const
        {
            return _id;
        }

        const char * getMessageString() const
        {
            return _format;
        }

        bool isFreeForm() const
        {
            return _format == nullptr;
        }

    private:

        const Level        _level;
        const Id           _id;
        const char * const _format; // ex: "Price is: %f"
};

}

#endif

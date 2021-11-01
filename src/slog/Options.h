#pragma once
#ifndef SLOG_OPTIONS_H
#define SLOG_OPTIONS_H

#include <map>
#include <variant>
#include <string>
#include <stdexcept>
#include <initializer_list>
#include <slog/Level.h>

namespace slog
{

extern const std::string OPT_USE_RAW_LOGGER;
extern const std::string OPT_ASYNC;
extern const std::string OPT_MULTIFILE;
extern const std::string OPT_LOG_LEVEL;
extern const std::string OPT_SHORT_LOG_LEVEL;
extern const std::string OPT_TS_WITH_DATE;
extern const std::string OPT_TS_PRECISION;
extern const std::string OPT_LOG_EVENT_TIME;
extern const std::string OPT_LOG_CHANNEL_NAME;
extern const std::string OPT_LOG_THREAD_PID;
extern const std::string OPT_BG_THREAD_AFFINITY;
extern const std::string OPT_BG_THREAD_NAME;
extern const std::string OPT_INITIAL_RECORD_POOL_SIZE;
extern const std::string OPT_SEND_ALL_ON_EXIT;

class Options
{
    public:

        using Value = typename std::variant< bool, char, int, long, std::string, Level >;

        Options() = default;

        Options( std::initializer_list< std::pair< std::string, Value > > opts );

        template< typename T >
        void put( const std::string & key, const T & value )
        {
            _options[ key ] = value;
        }

        template< typename T >
        const T & get( const std::string & key, const T & defaultValue ) const
        {
            auto it = _options.find( key );
            return it == _options.end() ? defaultValue : std::get<T>( it->second );
        }

        template< typename T >
        const T & get( const std::string & key ) const
        {
            auto it = _options.find( key );
            if( it == _options.end() )
            {
                throw std::invalid_argument( key );
            }
            return std::get<T>( it->second );
        }

        bool has( const std::string & key ) const
        {
            return _options.find( key ) != _options.end();
        }

    private:

        std::map< std::string, Value > _options;

};


}

#endif

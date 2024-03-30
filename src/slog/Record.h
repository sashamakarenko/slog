#pragma once
#ifndef SLOG_RECORD_H
#define SLOG_RECORD_H

#include <slog/Format.h>
#include <memory>
#include <ostream>

namespace slog
{

struct PermanentCharPtr
{
    PermanentCharPtr( const char * ptr ): data{ ptr }{}
    const char * const data;
};

enum class ArgType: uint16_t
{
    Char,
    UChar,
    Short,
    UShort,
    Int,
    UInt,
    Long,
    ULong,
    Float,
    Double,
    CharPtr,
    PermCharPtr,
    String,
    StringView
};

template<typename T> constexpr ArgType getArgType();

template<> constexpr ArgType getArgType< char                     >(){ return ArgType::Char       ; }
template<> constexpr ArgType getArgType< unsigned char            >(){ return ArgType::UChar      ; }
template<> constexpr ArgType getArgType< short                    >(){ return ArgType::Short      ; }
template<> constexpr ArgType getArgType< unsigned short           >(){ return ArgType::UShort     ; }
template<> constexpr ArgType getArgType< int                      >(){ return ArgType::Int        ; }
template<> constexpr ArgType getArgType< unsigned int             >(){ return ArgType::UInt       ; }
template<> constexpr ArgType getArgType< long                     >(){ return ArgType::Long       ; }
template<> constexpr ArgType getArgType< unsigned long            >(){ return ArgType::ULong      ; }
template<> constexpr ArgType getArgType< float                    >(){ return ArgType::Float      ; }
template<> constexpr ArgType getArgType< double                   >(){ return ArgType::Double     ; }
template<> constexpr ArgType getArgType< const char *             >(){ return ArgType::CharPtr    ; }
template<> constexpr ArgType getArgType< PermanentCharPtr         >(){ return ArgType::PermCharPtr; }
template<> constexpr ArgType getArgType< std::string              >(){ return ArgType::String     ; }
template<> constexpr ArgType getArgType< std::string_view         >(){ return ArgType::StringView ; }

class Channel;

class Record
{
    public:

        using Ptr = std::shared_ptr<Record>;

        virtual void insert( char                     arg ) = 0;
        virtual void insert( short                    arg ) = 0;
        virtual void insert( int                      arg ) = 0;
        virtual void insert( long                     arg ) = 0;
        virtual void insert( unsigned char            arg ) = 0;
        virtual void insert( unsigned short           arg ) = 0;
        virtual void insert( unsigned int             arg ) = 0;
        virtual void insert( unsigned long            arg ) = 0;
        virtual void insert( double                   arg ) = 0;
        virtual void insert( float                    arg ) = 0;
        virtual void insert( const char *             arg ) = 0;
        virtual void insert( const PermanentCharPtr & arg ) = 0;
        virtual void insert( const std::string &      arg ) = 0;
        virtual void insert( const std::string_view & arg ) = 0;

        virtual void prepare();
        virtual void reset();

        Channel & getChannel()
        {
            return _channel;
        }

        const Format * getFormat() const
        {
            return _format;
        }

        void setFormat( const Format * fmt )
        {
            _format = fmt;
        }

    protected:

        explicit Record( Channel & channel, const Format * fmt )
        : _format{ fmt }
        , _channel{ channel } 
        {
        }

        virtual ~Record();
    
    private:

        const Format * _format;
        Channel      & _channel;
};

}

template< typename T >
inline slog::Record & operator << ( slog::Record & rec, const T & value )
{
    rec.insert( value );
    return rec;
}

#if __arm__ == 1
#define PCP_TYPE unsigned int
#else
#define PCP_TYPE unsigned long
#endif

inline slog::PermanentCharPtr operator "" _pcp( const char * ptr, PCP_TYPE ){ return slog::PermanentCharPtr( ptr ); }

inline std::ostream & operator << ( std::ostream & os, const slog::PermanentCharPtr & ptr )
{
    return os << ptr.data;
}

#endif

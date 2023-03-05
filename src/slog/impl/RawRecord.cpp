#include <slog/impl/RawRecord.h>
#include <cstring>
#include <stdexcept>

namespace slog::impl
{

RawRecord::RawRecord( Channel & channel, const Format * fmt ): 
    Record( channel, fmt ),
    _buf{},
    _threadId{0}
{
    _buf.reserve( 1024 );
}

RawRecord::~RawRecord()
{
}

void RawRecord::prepare()
{
    _buf.clear();
}

void RawRecord::toAscii( std::ostream & os )
{
    size_t pos = 0;
    size_t len = _buf.size();
    while( pos < len )
    {
        if( pos > 0 )
        {
            os << ' ';
        }

        ArgType atype = *reinterpret_cast<const ArgType*>( & _buf[pos] );
        pos += sizeof( ArgType );

        switch( atype )
        {
            case ArgType::Char       :
                {
                    const char * ptr = & _buf[pos];
                    os << *ptr;
                    pos += sizeof( char );
                    break;
                }
            case ArgType::UChar      :
                {
                    const unsigned char * ptr = reinterpret_cast< const unsigned char * >( & _buf[pos] );
                    os << *ptr;
                    pos += sizeof(unsigned char);
                    break;
                }
            case ArgType::Short      :
                {
                    const short * ptr = reinterpret_cast< const short * >( & _buf[pos] );
                    os << *ptr;
                    pos += sizeof(short);
                    break;
                }
            case ArgType::UShort     :
                {
                    const unsigned short * ptr = reinterpret_cast< const unsigned short * >( & _buf[pos] );
                    os << *ptr;
                    pos += sizeof(unsigned short);
                    break;
                }
            case ArgType::Int        :
                {
                    const int * ptr = reinterpret_cast< const int * >( & _buf[pos] );
                    os << *ptr;
                    pos += sizeof(int);
                    break;
                }
            case ArgType::UInt       :
                {
                    const unsigned int * ptr = reinterpret_cast< const unsigned int * >( & _buf[pos] );
                    os << *ptr;
                    pos += sizeof(unsigned int);
                    break;
                }
            case ArgType::Long       :
                {
                    const long * ptr = reinterpret_cast< const long * >( & _buf[pos] );
                    os << *ptr;
                    pos += sizeof(long);
                    break;
                }
            case ArgType::ULong      :
                {
                    const unsigned long * ptr = reinterpret_cast< const unsigned long * >( & _buf[pos] );
                    os << *ptr;
                    pos += sizeof(unsigned long);
                    break;
                }
            case ArgType::Float      :
                {
                    float value;
                    memcpy( &value, & _buf[pos], sizeof(value) );
                    os << value;
                    pos += sizeof(value);
                    break;
                }
            case ArgType::Double     :
                {
                    double value;
                    memcpy( &value, & _buf[pos], sizeof(value) );
                    os << value;
                    pos += sizeof(value);
                    break;
                }
            case ArgType::CharPtr    :
            case ArgType::String     :
            case ArgType::StringView :
                {
                    const std::size_t * ptr = reinterpret_cast< const std::size_t * >( & _buf[pos] );
                    os << & _buf[pos+sizeof(std::size_t)];
                    pos += (*ptr) + sizeof(std::size_t);
                    break;
                }
            case ArgType::PermCharPtr:
                {
                    const PermanentCharPtr * ptr = reinterpret_cast< const PermanentCharPtr * >( & _buf[pos] );
                    os << ptr->data;
                    pos += sizeof(PermanentCharPtr);
                    break;
                }
            default:
                {
                    throw std::invalid_argument( "RawRecord: unknown arg type:" + std::to_string( (unsigned short)atype ) );
                }
        }
    }
}

template<typename T>
inline void pushValue( std::vector<char> & buf, const T & arg )
{

    buf.insert( buf.end(), reinterpret_cast<const char *>(&arg), reinterpret_cast<const char *>(&arg) + sizeof(T) );
}

template<>
inline void pushValue<const char *>( std::vector<char> & buf, const char * const & ptr )
{
    std::size_t sz = strlen(ptr)+1;
    pushValue( buf, sz );
    buf.insert( buf.end(), ptr, ptr + sz );
}

template<>
inline void pushValue<std::string>( std::vector<char> & buf, const std::string & str )
{
    std::size_t sz = str.length()+1;
    pushValue( buf, sz );
    buf.insert( buf.end(), str.c_str(), str.c_str() + sz );
}

template<typename T>
inline void push( std::vector<char> & buf, const T & arg )
{
    ArgType atype = getArgType<T>();
    pushValue( buf, (unsigned short)atype );
    pushValue( buf, arg );
}

void RawRecord::insert( char             arg )
{
    push( _buf, arg );
}

void RawRecord::insert( short            arg )
{
    push( _buf, arg );
}

void RawRecord::insert( int              arg )
{
    push( _buf, arg );
}

void RawRecord::insert( long             arg )
{
    push( _buf, arg );
}

void RawRecord::insert( unsigned char    arg )
{
    push( _buf, arg );
}

void RawRecord::insert( unsigned short   arg )
{
    push( _buf, arg );
}

void RawRecord::insert( unsigned int     arg )
{
    push( _buf, arg );
}

void RawRecord::insert( unsigned long    arg )
{
    push( _buf, arg );
}

void RawRecord::insert( double           arg )
{
    push( _buf, arg );
}

void RawRecord::insert( float            arg )
{
    push( _buf, arg );
}

void RawRecord::insert( const char *     arg )
{
    push( _buf, arg );
}

void RawRecord::insert( const PermanentCharPtr & arg )
{
    push( _buf, arg );
}

void RawRecord::insert( const std::string &      arg )
{
    push( _buf, arg );
}

void RawRecord::insert( const std::string_view & arg )
{
    push( _buf, arg );
}
    
}

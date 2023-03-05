#include <slog/impl/StreamRecord.h>

namespace slog::impl
{

StreamRecord::StreamRecord( Channel & channel, const Format * fmt, std::ostream & os ): 
    Record( channel, fmt ),
    _stream{ os },
    _pos{ 0 }
{
}

StreamRecord::~StreamRecord()
{
}

void StreamRecord::prepare()
{
    _pos = 0;
    insertNextFormatFragment();
}

void StreamRecord::flush()
{
    _stream.flush();
}

void StreamRecord::insertNextFormatFragment()
{
    const Format * fmt = getFormat();
    if( fmt == nullptr || fmt->getMessageString() == nullptr )
    {
        return;
    }

    const char * cur = fmt->getMessageString() + _pos;
    while( *cur )
    {
        if( *cur == '%' )
        {
            ++_pos;
            return;
        }
        _stream << *cur++;
        ++_pos;
    }
}

void StreamRecord::insert( char             arg )
{
    _stream << arg;
    insertNextFormatFragment();
}

void StreamRecord::insert( short            arg )
{
    _stream << arg;
    insertNextFormatFragment();
}

void StreamRecord::insert( int              arg )
{
    _stream << arg;
    insertNextFormatFragment();
}

void StreamRecord::insert( long             arg )
{
    _stream << arg;
    insertNextFormatFragment();
}

void StreamRecord::insert( unsigned char    arg )
{
    _stream << arg;
    insertNextFormatFragment();
}

void StreamRecord::insert( unsigned short   arg )
{
    _stream << arg;
    insertNextFormatFragment();
}

void StreamRecord::insert( unsigned int     arg )
{
    _stream << arg;
    insertNextFormatFragment();
}

void StreamRecord::insert( unsigned long    arg )
{
    _stream << arg;
    insertNextFormatFragment();
}

void StreamRecord::insert( double           arg )
{
    _stream << arg;
    insertNextFormatFragment();
}

void StreamRecord::insert( float            arg )
{
    _stream << arg;
    insertNextFormatFragment();
}

void StreamRecord::insert( const char *     arg )
{
    _stream << arg;
    insertNextFormatFragment();
}

void StreamRecord::insert( const PermanentCharPtr & arg )
{
    _stream << arg;
    insertNextFormatFragment();
}

void StreamRecord::insert( const std::string &      arg )
{
    _stream << arg;
    insertNextFormatFragment();
}

void StreamRecord::insert( const std::string_view & arg )
{
    _stream << arg;
    insertNextFormatFragment();
}
    
}

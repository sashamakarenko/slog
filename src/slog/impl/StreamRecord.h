#pragma once
#ifndef SLOG_STREAM_RECORD_H
#define SLOG_STREAM_RECORD_H

#include <slog/Record.h>
#include <ostream>

namespace slog::impl
{

class StreamRecord: public Record
{
    public:

        using Ptr = std::shared_ptr< StreamRecord >;

        StreamRecord( Channel & channel, const Format * fmt, std::ostream & os );

        virtual ~StreamRecord();
    
        virtual void insert( char             arg ) override;
        virtual void insert( short            arg ) override;
        virtual void insert( int              arg ) override;
        virtual void insert( long             arg ) override;
        virtual void insert( unsigned char    arg ) override;
        virtual void insert( unsigned short   arg ) override;
        virtual void insert( unsigned int     arg ) override;
        virtual void insert( unsigned long    arg ) override;
        virtual void insert( double           arg ) override;
        virtual void insert( float            arg ) override;
        virtual void insert( const char *     arg ) override;
        virtual void insert( const PermanentCharPtr & arg ) override;
        virtual void insert( const std::string &      arg ) override;
        virtual void insert( const std::string_view & arg ) override;

        virtual void prepare() override;

        void flush();

        std::ostream & getStream()
        {
            return _stream;
        }

        int getThreadId() const
        {
            return _threadId;
        }

        void setThreadId( int tid )
        {
            _threadId = tid;
        }

    private:

        void insertNextFormatFragment();

        std::ostream & _stream;
        unsigned       _pos;
        int            _threadId;
};

}

#endif

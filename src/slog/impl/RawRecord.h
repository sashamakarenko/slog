#pragma once
#ifndef SLOG_RAW_RECORD_H
#define SLOG_RAW_RECORD_H

#include <slog/Record.h>
#include <vector>

namespace slog::impl
{

class RawRecord: public Record
{
    public:

        using Ptr = std::shared_ptr< RawRecord >;

        RawRecord( Channel & channel, const Format * fmt );

        virtual ~RawRecord();
    
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

        virtual void prepare() override;

        void toAscii( std::ostream & os );

        int getThreadId() const
        {
            return _threadId;
        }

        void setThreadId( int tid )
        {
            _threadId = tid;
        }

    private:

        std::vector< char > _buf;
        int                 _threadId;
};

}

#endif

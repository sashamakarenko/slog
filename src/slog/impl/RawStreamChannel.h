#pragma once
#ifndef SLOG_RAW_STRSTREAM_CHANNEL_H
#define SLOG_RAW_STRSTREAM_CHANNEL_H

#include <slog/impl/RawRecord.h>
#include <slog/impl/ReusableRecordsPool.h>
#include <slog/impl/RecordUnlocker.h>
#include <slog/Channel.h>
#include <mutex>
#include <stack>
#include <set>

namespace slog::impl
{

class RawStreamChannel: public Channel, private ReusableRecordsPool<RawRecord>
{

    public:

        RawStreamChannel( ChannelFactory & factory, const std::string & id, std::ostream & out, std::ostream & err, std::mutex & mtx, const Options & options );

        virtual ~RawStreamChannel() override;

        virtual void asyncWriteRecord( Record::Ptr rec ) override;

    protected:

        virtual Record::Ptr createRecord( const Format * fmt ) override;

        virtual void writeRecord( Record::Ptr rec ) override;

        virtual void insertLogPrefix( std::ostream & os, RawRecord & rec );

        virtual RawRecord * newRecord( const Format * fmt ) override;

        bool saveFormat( std::ostream & s, const Format * fmt );

        bool                          _async;
        bool                          _logChannelName;
        bool                          _logThreadId;

    private:

        std::ostream                & _out;
        std::ostream                & _err;
        std::mutex                  & _mtx;
        RawRecord                     _syncRecord;
        RecordUnlocker<RawRecord>     _recUnlocker;
        std::set< Format::Id >        _knownFormats;
};

}

#endif

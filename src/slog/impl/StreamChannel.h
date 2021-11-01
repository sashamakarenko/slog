#pragma once
#ifndef SLOG_STRSTREAM_CHANNEL_H
#define SLOG_STRSTREAM_CHANNEL_H

#include <slog/impl/StrStreamRecord.h>
#include <slog/impl/ReusableRecordsPool.h>
#include <slog/impl/RecordUnlocker.h>
#include <slog/Channel.h>
#include <mutex>
#include <stack>

namespace slog::impl
{

class StreamChannel: public Channel, private ReusableRecordsPool<StreamRecord>
{

    public:

        StreamChannel( ChannelFactory & factory, const std::string & id, std::ostream & out, std::ostream & err, std::mutex & mtx, const Options & options );

        virtual ~StreamChannel() override;

        virtual void asyncWriteRecord( Record::Ptr rec ) override;

    protected:

        virtual Record::Ptr createRecord( const Format * fmt ) override;

        virtual void writeRecord( Record::Ptr rec ) override;

        virtual void insertLogPrefix( std::ostream & os, StreamRecord & rec );

        virtual StreamRecord * newRecord( const Format * fmt ) override;

        bool                          _async;
        bool                          _logChannelName;
        bool                          _logThreadId;

    private:

        std::ostream                & _out;
        std::ostream                & _err;
        std::mutex                  & _mtx;
        StreamRecord                  _outSyncRecord;
        StreamRecord                  _errSyncRecord;
        RecordUnlocker<StreamRecord>  _recUnlocker;

};

}

#endif

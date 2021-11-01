#pragma once
#ifndef SLOG_CHANNEL_FACTORY_H
#define SLOG_CHANNEL_FACTORY_H

#include <string>
#include <map>
#include <memory>
#include <mutex>
#include <slog/Channel.h>
#include <slog/Options.h>

namespace slog
{

struct ChannelDeleter;

class ChannelFactory
{
    public:

        virtual Channel & getChannel( const std::string & id, const Options & options );

        virtual const std::string & getName() const = 0;

        static bool setInstance( ChannelFactory * cf );

        static ChannelFactory * getInstance();

        virtual long queueRecord( Record::Ptr rec );

    protected:

        friend struct FactoryDeleter;

        ChannelFactory();

        virtual ~ChannelFactory();

        virtual Channel::Ptr createChannel( const std::string & id, const Options & options ) = 0;

    private:

        // to be used by factories in their createChannel() implementations
        std::mutex                                         _channelsGuard;
        std::map< std::string, std::shared_ptr<Channel> >  _channels;

};

}

#endif

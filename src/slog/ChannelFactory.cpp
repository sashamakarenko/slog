#include <slog/ChannelFactory.h>
#include <memory>
#include <iostream>

namespace slog
{

struct FactoryDeleter
{
    void operator()( ChannelFactory * cf )
    {
        std::cout << "deleted channel factory: " << cf->getName() << "\n";
        delete cf;
    }
};

struct ChannelDeleter
{
    void operator()( Channel * ch ) noexcept
    {
        std::cout << "deleted channel: " << ch->getId() << "\n";
        delete ch;
    }
};

ChannelDeleter channelDeleter;

namespace
{
    std::unique_ptr<ChannelFactory,FactoryDeleter> instance;
}

bool ChannelFactory::setInstance( ChannelFactory * cf )
{
    if( instance )
    {
        return false;
    }

    instance.reset( cf );
    return true;
}

ChannelFactory * ChannelFactory::getInstance()
{
    return instance.get();
}

ChannelFactory::ChannelFactory()
{
}

ChannelFactory::~ChannelFactory()
{   
}

Channel & ChannelFactory::getChannel( const std::string & id, const Options & options )
{
    std::scoped_lock<std::mutex> protectChannels( _channelsGuard );
    Channel::Ptr & ch = _channels[ id ];
    if( not ch )
    {
        ch = createChannel( id, options );
    }
    return *ch.get();
}

long ChannelFactory::queueRecord( Record::Ptr rec )
{
    return -1L;
}

}

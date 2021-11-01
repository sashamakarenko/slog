#include <slog/ChannelFactory.h>

namespace slog::impl
{

class MuteChannelFactory: public ChannelFactory
{
    public:
        
        MuteChannelFactory();

        Channel & getChannel( const std::string & id, const Options & options ) override;

        virtual const std::string & getName() const override;
    
    protected:

        virtual Channel::Ptr createChannel( const std::string & id, const Options & options ) override;

    private:
        
        Channel::Ptr _channel;

};

}


#include <slog/impl/MuteChannelFactory.h>
#include <slog/Channel.h>

namespace slog::impl
{

class MuteRecord: public Record
{
    public:

        MuteRecord( Channel & ch ): Record( ch, nullptr ){}
        virtual ~MuteRecord(){}
    
        virtual void insert( char             arg ) override {}
        virtual void insert( short            arg ) override {}
        virtual void insert( int              arg ) override {}
        virtual void insert( long             arg ) override {}
        virtual void insert( unsigned char    arg ) override {}
        virtual void insert( unsigned short   arg ) override {}
        virtual void insert( unsigned int     arg ) override {}
        virtual void insert( unsigned long    arg ) override {}
        virtual void insert( double           arg ) override {}
        virtual void insert( float            arg ) override {}
        virtual void insert( const char *     arg ) override {}
        virtual void insert( const PermanentCharPtr & arg ) override {}
        virtual void insert( const std::string &      arg ) override {}
};


class MuteChannel: public Channel
{

    public:

        MuteChannel( ChannelFactory & factory ): 
            Channel( factory, "MuteChannel", Level::MUTE ),
            _rec( new MuteRecord( *this ) )
        {
        }

        virtual ~MuteChannel() override 
        {
        }

        virtual Record::Ptr createRecord( const Format * fmt ) override
        {
            return _rec;
        }

        virtual void writeRecord( Record::Ptr rec ) override
        {
        }

    Record::Ptr _rec;
};

MuteChannelFactory::MuteChannelFactory():
    _channel{ std::make_shared<MuteChannel>( *this ) }
{
}

Channel & MuteChannelFactory::getChannel( const std::string & id, const Options & options )
{
    return *_channel.get();
}

Channel::Ptr MuteChannelFactory::createChannel( const std::string & id, const Options & options )
{
    return _channel;
}

const std::string & MuteChannelFactory::getName() const
{
    static std::string name( "MuteChannelFactory" );
    return name;
}


}

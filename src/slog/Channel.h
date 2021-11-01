#pragma once
#ifndef SLOG_CHANNEL_H
#define SLOG_CHANNEL_H

#include <slog/Record.h>
#include <slog/Message.h>

namespace slog
{

class Channel;
class ChannelFactory;
class Options;

class Channel: public std::enable_shared_from_this<Channel>
{
    public:

        using Ptr = std::shared_ptr<Channel>;

        template< typename Msg, typename... Args >
        void log( const Args&... args )
        {
            static_assert( std::is_same< typename Msg::AllArgs, typename std::tuple<Args...> >() );
            // static_cast< const typename Msg::AllArgs* >( (const typename std::tuple<Args...> *)nullptr );

            if( not isLevelReached( _level, Msg::getLevel() ) )
            {
                return;
            }
            
            Record::Ptr rec = createRecord( Msg::getFormat() );
            //( rec->insert(args), ... );
            ( *rec.get() << ... << args );
            writeRecord( rec );
        }

        template< typename... Args >
        void log( Level lvl, const Args&... args )
        {
            if( not isLevelReached( _level, lvl ) )
            {
                return;
            }
            
            Record::Ptr rec = createRecord( getFreeformFormat( lvl ) );
            ( *rec.get() << ... << args );
            writeRecord( rec );
        }

        template< typename... Args >
        void panic( const Args&... args )
        {
            log( Level::PANIC, args... );
        }

        template< typename... Args >
        void error( const Args&... args )
        {
            log( Level::ERROR, args... );
        }

        template< typename... Args >
        void warning( const Args&... args )
        {
            log( Level::WARNING, args... );
        }

        template< typename... Args >
        void info( const Args&... args )
        {
            log( Level::INFO, args... );
        }

        template< typename... Args >
        void debug( const Args&... args )
        {
            log( Level::DEBUG, args... );
        }

        template< typename... Args >
        void trace( const Args&... args )
        {
            log( Level::TRACE, args... );
        }


        const std::string & getId() const { return _id; }

        Level getLoglevel() const { return _level; }

        Channel() = delete;

        Channel( const Channel & ) = delete;
    
        virtual void asyncWriteRecord( Record::Ptr rec );

        static const Format * getFreeformFormat( Level lvl );

    protected:

        explicit Channel( ChannelFactory & factory, const std::string & id, Level lvl = Level::INFO );

        friend struct ChannelDeleter;
        virtual ~Channel() = 0;

        virtual Record::Ptr createRecord( const Format * fmt ) = 0;

        virtual void writeRecord( Record::Ptr rec ) = 0;

        ChannelFactory & getFactory()
        {
            return _factory;
        }

    private:

        ChannelFactory & _factory;
        std::string      _id;
        Level            _level;
};

extern const Options EmptyOptions;

Channel & createChannel( const std::string & id, const Options & options = EmptyOptions );

}

#endif

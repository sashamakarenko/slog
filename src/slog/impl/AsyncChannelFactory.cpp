#include <slog/impl/AsyncChannelFactory.h>

namespace slog::impl
{

AsyncChannelFactory::AsyncChannelFactory( const Options & opts ):
    ChannelFactory(),
    _queue{ opts }
{
}

long AsyncChannelFactory::queueRecord( Record::Ptr rec )
{
    return _queue.queueRecord( rec );
}


}

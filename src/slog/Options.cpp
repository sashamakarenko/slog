#include <slog/Options.h>

namespace slog
{

const std::string OPT_USE_RAW_LOGGER           = "use.raw.logger";
const std::string OPT_ASYNC                    = "async";
const std::string OPT_MULTIFILE                = "multifile";
const std::string OPT_LOG_LEVEL                = "log.level";
const std::string OPT_LOG_EVENT_TIME           = "log.event.time";
const std::string OPT_TS_WITH_DATE             = "ts.with.date";
const std::string OPT_TS_PRECISION             = "ts.precision";
const std::string OPT_SHORT_LOG_LEVEL          = "short.log.level";
const std::string OPT_LOG_CHANNEL_NAME         = "log.channel.name";
const std::string OPT_LOG_THREAD_PID           = "log.thread.pid";
const std::string OPT_BG_THREAD_AFFINITY       = "bg.thread.affinity";
const std::string OPT_BG_THREAD_NAME           = "bg.thread.name";
const std::string OPT_INITIAL_RECORD_POOL_SIZE = "initial.record.pool.size";
const std::string OPT_SEND_ALL_ON_EXIT         = "send.all.on.exit";

Options::Options( std::initializer_list< std::pair< std::string, Value > > opts )
{
    _options.insert( opts.begin(), opts.end() );
}

}


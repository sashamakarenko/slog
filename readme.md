# slog - Structured Logger for C++

The challenge is to provide a flexible logging framework for C++ apps with three major features:
1. Separate interface from implementation.
2. Apps will be able to share a type safe API with reusable formats in order to offer a uniform output across all logs.
3. Give the implementations an opportunity to target their optimization for latency, throughput or/and volume if necessary.

## First glance

With general purpose logging APIs it is quite common to see the following kind of things:
```c++
log.error( "Bad Order: qty=%d px=%f", 10, 2.3 );
// or
log( log::ERROR, "Bad Order: qty=", 10, " px=", 2.3 );
// or
log.debug( "Login: new session for user ", userName );
```

In a latency sensitive context such calls are wrapped in a macro to avoid useless formatting. Nonetheless, when invoked it will presumably require formatting, allocations and copying.

With slog a similar piece of code will be:

```c++
out.log<BadOrder>( 10, 2.3 );
// and
out.log<NewSession>( userName );
```
where BadOrder and NewSession are predefined formats with their log levels, message strings and argument types.

## Separate interface from implementations
At the very beginning of your app (early in main for example) select one of already available implementations in slog or provide your own
```c++
slog::ChannelFactory::setInstance( new slog::impl::FileStreamChannelFactory( "out.log" ) );
slog::Channel & session = slog::createChannel( "session" );
slog::Channel & trading = slog::createChannel( "trading" );

```

then in the code:
```c++
...
session.log<NewSession>( userName );
...
trading.log<BadOrder>( 10, 2.3 );

// or a free form message (not optimal)
trading.debug( "Received ACK on order ", orderId, " with Market ID ", marketOrderId );

```


## Type safe API with reusable formats

In order the above example to work one has to declare the available message types first. Somewhere in a MyLogMessages.h for instance:
```c++
extern slog::Format NewSessionFmt;
typedef slog::Message< & NewSessionFmt, const char * > NewSession;

extern slog::Format BadOrderFmt;
typedef slog::Message< & BadOrderFmt, int, double > BadOrder;
```

then in MyLogMessages.cpp we define the formats
```c++
slog::Format NewSessionFmt( slog::Level::INFO, "NS", "User name=%" );
slog::Format BadOrderFmt( slog::Level::ERROR, "BO", "Bad Order: qty=% px=%" );
```

1. Since the argument types are part of the message signature, the actually provided values will be verified by the compiler.
2. The log level is embedded in the Format object and no longer required during invocation.
3. One can maintain a library of all available messages and share it as a component to ensure a normalized output across all apps.

## Optimization opportunities
A message Format is defined with a unique 2-char ID and the message string itself. This gives the implementation an opportunity not to format the string during log invocation and even not to log the formatted message at all but rather its ID and arguments.

Such a sparse log may be done in binary or ASCII. The latter remains quite compact, competitively fast and still human readable.
The StreamChannel implementation available in slog provides this possibility of raw ASCII logging. 
The very first time a message is logged, its formatting string is logged only once with its unique ID.

Schematically, for the sake of simplicity let us assume an implementation uses F as first character to log the formats and I, W and E to log information, warnings and errors respectively. In this case in a log they will appear like:
```
F 617f81cc session NS User name=%
I 617f81cc session NS Alejandro
F 617f81dd trading BO Bad Order: qty=% px=%
I 617f81e9 session NS TradingBot123
F 617f81dd trading BO 1000 234.5
...

```
For more see src/test/TestStreamChannel.cpp.

## Examples

To compile the examples you will have to clone the makefile project next to slog:

```
$> git clone https://github.com/sashamakarenko/makefile.git makefile
$> git clone https://github.com/sashamakarenko/slog.git slog
$> cd slog
$> make
$> make check
```

[![HitCount](https://hits.dwyl.com/sashamakarenko/slog.svg?style=flat)](http://hits.dwyl.com/sashamakarenko/slog)


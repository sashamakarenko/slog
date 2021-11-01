#pragma once

#include <slog/Channel.h>

extern slog::Format BadOrderFmt;
typedef slog::Message< & BadOrderFmt, int, double > ErrorBadOrder;

extern slog::Format AllIntTypesFmt;
typedef slog::Message< & AllIntTypesFmt, char, short, int, long, unsigned char, unsigned short, unsigned int, unsigned long > AllIntTypes;

extern slog::Format NoArgsMessageFmt;
typedef slog::Message< & NoArgsMessageFmt > NoArgsMessage;

extern slog::Format ShowUserFmt;
typedef slog::Message< & ShowUserFmt, const char * > ShowUser;

extern slog::Format PermamemtCharPanicFmt;
typedef slog::Message< & PermamemtCharPanicFmt, slog::PermanentCharPtr > PermanentString;

typedef slog::Message< nullptr, const char * > NUllFmtMsg;

void logAllMessages( slog::Channel & channel );

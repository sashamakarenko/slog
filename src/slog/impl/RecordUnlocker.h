#pragma once
#ifndef SLOG_RECORD_UNLOCKER_H
#define SLOG_RECORD_UNLOCKER_H

#include <mutex>

namespace slog::impl
{

template< typename RecType >
struct RecordUnlocker
{
    RecordUnlocker( std::mutex & mtx ): _mtx( mtx ){}

    void operator()( RecType * ) noexcept
    {
        _mtx.unlock();
    }

    std::mutex & _mtx;
};

}

#endif

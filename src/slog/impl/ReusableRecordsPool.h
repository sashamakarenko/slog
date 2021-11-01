#pragma once
#ifndef SLOG_REUSABLE_RECORDS_POOL_H
#define SLOG_REUSABLE_RECORDS_POOL_H

#include <mutex>
#include <stack>

namespace slog
{
    class Format;
}

namespace slog::impl
{

template< typename RecordType >
class ReusableRecordsPool
{

    protected:

        ReusableRecordsPool()
        : _isDestoying{false}
        , _recRecycler{this}
        {
        }

        virtual ~ReusableRecordsPool()
        {
            _isDestoying = true;
        }

        typename RecordType::Ptr popOrCreateRecord( const Format * fmt )
        {
            {
                std::unique_lock<std::mutex> protectQueue( _recordsGuard );
                if( _records.size() )
                {
                    auto rec = _records.top();
                    _records.pop();
                    rec->setFormat( fmt );
                    return rec;
                }
            }
            
            return typename RecordType::Ptr( newRecord( fmt ), _recRecycler  );
        }        

        virtual RecordType * newRecord( const Format * fmt ) = 0;

        void recycleRecord( RecordType * rec )
        {
            rec->reset();
            std::unique_lock<std::mutex> protectQueue( _recordsGuard );
            if( _isDestoying )
            {
                delete rec;
            }
            else
            {
                _records.emplace( rec, _recRecycler );
            }
        }

        struct RecordRecycler
        {
            void operator()( RecordType * rec ) noexcept
            {
                pool->recycleRecord( rec );
            }
            ReusableRecordsPool *pool;
        };

        friend struct RecordRecycler;

    private:

        bool                            _isDestoying;
        RecordRecycler                  _recRecycler;
        std::mutex                      _recordsGuard;
        std::stack< typename RecordType::Ptr > _records;

};

}

#endif

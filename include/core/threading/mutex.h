#pragma once

#include <core/compiler.h>

#include <pthread.h>

namespace core
{
    class mutex
    {
    public:
        mutex();
        ~mutex();
        
        /**
         * Lock the mutex, or wait until it can be locked
         */
        void lock();
        
        /**
         * Returns true when the lock was successfull
         */
        bool try_lock();
        
        /**
         Unlock the mutex
         */
        void unlock();
        
        /**
         * For internal use only.
         */
        inline pthread_mutex_t& os_mutex()
        {
            return _mutex;
        }
    private:
        pthread_mutex_t _mutex;
    };
    
    class scoped_lock
    {
        CORE_NO_COPY(scoped_lock);
        CORE_NO_MOVE(scoped_lock);

        mutex _mutex;
    public:
        inline scoped_lock()
        {
            _mutex.lock();
        }
        
        inline ~scoped_lock()
        {
            _mutex.unlock();
        }
    };
};

#pragma once

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
    public:
        inline scoped_lock()
        {
            _mutex.lock();
        }
        
        inline ~scoped_lock()
        {
            _mutex.unlock();
        }
        
        scoped_lock(const scoped_lock&) = delete;
        scoped_lock(scoped_lock&&) = delete;
        
        scoped_lock& operator=(const scoped_lock&) = delete;
        scoped_lock& operator=(scoped_lock&&) = delete;
    private:
        mutex _mutex;
    };
};

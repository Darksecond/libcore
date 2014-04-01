#pragma once

#include <core/compiler.h>
#include <pthread.h>
#include <cassert>

namespace core
{
    template <typename T>
    class thread_specific_ptr
    {
        CORE_NO_COPY(thread_specific_ptr);
        CORE_NO_MOVE(thread_specific_ptr);
        pthread_key_t _key;
    public:
        thread_specific_ptr()
        {
            pthread_key_create(&_key, nullptr);
        }
        
        ~thread_specific_ptr()
        {
            pthread_key_delete(_key);
        }
        
        thread_specific_ptr& operator=(T* p)
        {
            set(p);
            return *this;
        }
        
        inline void set(T* p)
        {
            pthread_setspecific(_key, p);
        }
        
        inline T* get() const
        {
            return static_cast<T*>(pthread_getspecific(_key));
        }
        
        inline T* operator->() const
        {
            return get();
        }
        
        inline T& operator*() const
        {
            assert(get() != nullptr);
            return *get();
        }
    };
};

#pragma once

#include <pthread.h>

namespace core
{
    class mutex;
    class condition_variable
    {
    public:
        condition_variable();
        ~condition_variable();
        
        /**
         * Signal one waiting thread to resume.
         */
        void signal_one();
        
        /**
         * Signal all waiting threads to resume.
         */
        void signal_all();
        
        /**
         * Wait for a signal, will unlock mutex.
         */
        void wait(mutex&);
    private:
        pthread_cond_t _condition;
    };
};

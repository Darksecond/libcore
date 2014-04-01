#pragma once

#include <core/compiler.h>
#include <pthread.h>

namespace core
{
    /*
     * This is a wrapper around native OS threads.
     * The API is abstracted so it will work on multiple platforms.
     */
    class thread
    {
        CORE_NO_MOVE(thread);
        CORE_NO_COPY(thread);

        enum class state_t
        {
            READY,
            RUNNING,
            SHOULD_STOP,
            STOPPED,
        };
    public:
        typedef void (*function)(const thread&);
        
        /**
         * This does not create an OS thread.
         */
        thread();
        
        /**
         * This just calls destroy().
         */
        ~thread();
        
        /**
         * Create and start a new OS thread, with name and function to execute.
         */
        void create(const char* name, function f);
        
        /**
         * Calls stop() followed by join().
         */
        void destroy();
        
        /**
         * Join on thread.
         */
        void join();
        
        /**
         * Tell thread to stop,
         * there is no guarentee the thread _will_ actually stop,
         * but it should.
         */
        void stop();
        
        /**
         * This will be true if the thread should stop.
         */
        bool should_stop() const;
        
        /**
         * This will be true if stop is not called.
         */
        bool continue_running() const;
        
        /**
         This will be true if the thread has ended.
         */
        bool is_stopped() const;
        
        /**
         * Yield back to the OS.
         */
        void yield();
    private:
        static void* thread_main_function(void* thread);
        function _function;
        state_t _state;
        pthread_t _thread;
        const char* _name;
    };
};

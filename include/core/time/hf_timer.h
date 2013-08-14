#pragma once

#include <core/types.h>
#include <core/platform.h>

namespace core
{
    /**
     * High frequency timer.
     * Usually has < millisecond resolution (depending on platform)
     */
    class hf_timer
    {
    public:
        /**
         * (Re)Start the timer.
         */
        void start();
    
        /**
         * get the current delta in nanoseconds.
         */
        double get_nanoseconds() const;
        
        /**
         * Get the current delta in seconds.
         */
        double get_seconds() const;
        
        /**
         * Get teh current delta in milliseconds.
         */
        double get_milliseconds() const;
        
    private:
#ifdef P_PLATFORM_APPLE
        uint64_t _start;
#endif
    };
};

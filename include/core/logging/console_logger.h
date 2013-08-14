#pragma once

#include <core/logging/log.h>

namespace core
{
    class console_logger : public logger
    {
    public:        
        //replace format and args with fixed_string?
        virtual void log(const core::source_info& source_info, int level, const char* channel, const char* format, va_list args);
    };
};

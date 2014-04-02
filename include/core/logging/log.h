#pragma once

#include <cstdarg>

#define CORE_SOURCEINFO core::source_info(__FILE__, __FUNCTION__, __LINE__)

#define CORE_LOG(level, channel, format, ...) core::log::log(CORE_SOURCEINFO, level, channel, format, ##__VA_ARGS__)
#define CORE_LDEBUG(channel, format, ...) core::log::log(CORE_SOURCEINFO, 4, channel, format, ##__VA_ARGS__)
#define CORE_LINFO(channel, format, ...) core::log::log(CORE_SOURCEINFO, 3, channel, format, ##__VA_ARGS__)
#define CORE_LWARNING(channel, format, ...) core::log::log(CORE_SOURCEINFO, 2, channel, format, ##__VA_ARGS__)
#define CORE_LERROR(channel, format, ...) core::log::log(CORE_SOURCEINFO, 1, channel, format, ##__VA_ARGS__)
#define CORE_LFATAL(channel, format, ...) core::log::log(CORE_SOURCEINFO, 0, channel, format, ##__VA_ARGS__)

namespace core
{
    struct source_info
    {
        inline source_info(const char* const file_, const char* const function_, const int line_) : file(file_), function(function_), line(line_)
        {
        }

        const char* const file;
        const char* const function;
        const int line;
    };
    
    class logger
    {
    public:
        virtual ~logger() {}
        
        //replace format and args with fixed_string?
        virtual void log(const core::source_info& source_info, int level, const char* channel, const char* format, va_list args) = 0;
    };
    
    //0 = fatal, 1 = error, 2 = warning, 3 = info, 4 = debug
    namespace log
    {
        void set_logger(logger* logger, int i);
        void log(const core::source_info& source_info, int level, const char* channel, const char* format, ...);
    };
};

#include <core/logging/console_logger.h>
#include <core/string/fixed_string.h>

#include <iostream>

void core::console_logger::log(const core::source_info& source_info, int level, const char* channel, const char* format, va_list args)
{
    core::fixed_string<512> log_message;
    log_message.append_fmt("[%i][%s][%s:%i] ", level, channel, source_info.file, source_info.line);
    log_message.append_fmt_v(format, args);
    
    std::cout << log_message.c_str() << std::endl;
}

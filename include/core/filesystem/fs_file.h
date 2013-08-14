#pragma once

#include <core/filesystem/file.h>

#include <fstream>

namespace core
{
    class fs_file : public file
    {
        std::fstream _stream;
    public:
        fs_file(const char* path, int mode, archive* owner);
        
        virtual size_t read(void* buffer, size_t buf_size);
        virtual void write(const void* buffer, size_t buf_size);
        virtual void skip(size_t amount);
        virtual void seek(size_t position);
        virtual bool eof() const;
        virtual size_t total_size();
    };
};

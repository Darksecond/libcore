#pragma once

#include <core/filesystem/archive.h>

namespace core
{
    class arena;
    
    class fs_archive : public archive
    {
        arena* _arena;
        const char* _directory;
    public:
        /**
         * directory is the 'working directory' for this archive.
         * arena is the memory arena used to create files in.
         */
        fs_archive(const char* directory, arena* arena);
        
        virtual file* open(const char* path, int mode) override;
        virtual void close(file* file) override;
    };
};

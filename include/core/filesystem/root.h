#pragma once

#include <core/types.h>
#include <core/containers/dynamic_array.h>

namespace core
{
    class archive;
    class arena;
    class file;
    
    class root
    {
        dynamic_array<archive*> _mounts;
    public:
        root(arena* arena, int capacity);
        
        void mount(archive*);
        void unmount(archive*);
        
        //TODO: replace int mode with something better
        /**
         * Open a file with path and mode.
         * Returns a nullptr if the file does not exist.
         */
        file* open(const char* path, int mode);
        
        /**
         * Close a previously opened with 'open'.
         */
        void close(file* file);
    };
};

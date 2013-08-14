#pragma once

namespace core
{
    class file;
    
    class archive
    {
    public:
        /**
         * Open a file with path and mode if it exists.
         * Returns nullptr if the file does not exist.
         */
        virtual file* open(const char* path, int mode) = 0;
        
        /**
         * Close a file previously opened.
         * This might also delete the file.
         */
        virtual void close(file* file) = 0;
    };
};

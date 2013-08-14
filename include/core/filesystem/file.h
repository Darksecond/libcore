#pragma once

#include <core/types.h>

namespace core
{
    class archive;
    
    class file
    {
        archive* _owner;
    public:
        file(archive* owner) : _owner(owner)
        {
        }
        
        virtual ~file()
        {
        }
        
        /**
         * Read into buffer for a maximum of buf_size bytes.
         * Returns the amount of bytes read.
         */
        virtual size_t read(void* buffer, size_t buf_size) = 0;
        
        /**
         * Write from buffer into file for buf_size bytes.
         */
        virtual void write(const void* buffer, size_t buf_size) = 0;
        
        template <typename T>
        inline size_t read(T& object)
        {
            return read(&object, sizeof(T));
        }
        
        template <typename T>
        inline void write(const T& object)
        {
            write(&object, sizeof(T));
        }
        
        //async_read
        //async_write
        
        //streaming stuff?
        
        /**
         * skip amount of bytes.
         */
        virtual void skip(size_t amount) = 0;
        
        /**
         * Seek to position in file.
         */
        virtual void seek(size_t position) = 0;
        virtual bool eof() const = 0; //or get_remaining_bytes
        virtual size_t total_size() = 0;
        
        archive* owner() const
        {
            return _owner;
        }
    };
};

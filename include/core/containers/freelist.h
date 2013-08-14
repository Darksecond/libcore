#pragma once

namespace core
{
    class freelist
    {
        freelist* next;
    public:
        inline freelist();
        inline freelist(void* start, void* end, size_t element_size);
        
        inline void* pop();
        inline void push(void* ptr);
    };
    
    inline freelist::freelist() : next(nullptr)
    {
    }
    
    inline freelist::freelist(void* start, void* end, size_t element_size) : next(nullptr)
    {
        assert(element_size >= sizeof(freelist*));
        
        union
        {
            void* as_void;
            char* as_char;
            freelist* as_freelist;
        };
        
        as_void = start;
        next = as_freelist;
        
        const size_t element_count = (static_cast<char*>(end) - as_char) / element_size;
        
        as_char += element_size;
        
        //initialize freelist chain
        freelist* runner = next;
        for(size_t i = 1; i < element_count; ++i)
        {
            runner->next = as_freelist;
            runner = runner->next;
            
            as_char += element_size;
        }
    }
    
    inline void* freelist::pop()
    {
        if(next == nullptr)
            return nullptr;
        
        freelist* head = next;
        next = head->next;
        
        return head;
    }
    
    inline void freelist::push(void* ptr)
    {
        assert(ptr);
        
        freelist* head = static_cast<freelist*>(ptr);
        head->next = next;
        next = head;
    }
};

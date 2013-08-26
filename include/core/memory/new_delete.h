#pragma once

#include <core/types.h>
#include <core/logging/log.h>

#include <type_traits>
#include <new>

#define CORE_NEW(arena, type, ...) (new ((arena).allocate(sizeof(type), alignof(type), 0, CORE_SOURCEINFO)) type(__VA_ARGS__))

#define CORE_DELETE(arena, object) core::memory_internals::delete_mem(arena, object, CORE_SOURCEINFO)

#define CORE_NEW_ARRAY(arena, type) core::memory_internals::new_array_mem<core::type_and_count<type>::Type>(arena, core::type_and_count<type>::Count, CORE_SOURCEINFO, core::bool_to_type<std::is_pod<core::type_and_count<type>::Type>::value>())

#define CORE_NEW_ARRAY_WITH_COUNT(arena, type, count) core::memory_internals::new_array_mem<type>(arena, count, CORE_SOURCEINFO, core::bool_to_type<std::is_pod<core::type_and_count<type>::Type>::value>())

#define CORE_DELETE_ARRAY(arena, ptr) core::memory_internals::delete_array_mem(arena, ptr, CORE_SOURCEINFO);

namespace core
{
    namespace memory_internals
    {
        typedef bool_to_type<false> NonPODType;
        typedef bool_to_type<true> PODType;
        
        template<class A, typename T>
        void delete_mem(A& arena, T* object, const source_info& info)
        {
            if(object)
            {
                object->~T();
                arena.free(object, info);
            }
        }
        
        template<typename T, class A>
        T* new_array_mem(A& arena, size_t count, const source_info& info, PODType)
        {
            return static_cast<T*>(arena.allocate(sizeof(T) * count, alignof(T), 0, info));
        }
        
        template<typename T, class A>
        T* new_array_mem(A& arena, size_t count, const source_info& info, NonPODType)
        {
            union
            {
                void* as_void;
                size_t* as_size_t;
                T* as_T;
            };
            
            as_void = arena.allocate( sizeof(T) * count + sizeof(size_t), alignof(T), sizeof(size_t) );
            
            *as_size_t++ = count;

            const T* const end = as_T + count;
            
            while(as_T < end)
            {
                new (as_T++) T;
            }
            
            return (as_T - count);
        }
        
        template<typename T, class A>
        void delete_array_mem(A& arena, T* ptr, const source_info& info, PODType)
        {
            arena.free(ptr, info);
        }
        
        template<typename T, class A>
        void delete_array_mem(A& arena, T* ptr, const source_info& info, NonPODType)
        {
            union
            {
                size_t* as_size_t;
                T* as_T;
            };
            
            as_T = ptr;
            
            const size_t count = as_size_t[-1];
            
            for(size_t i = count; i > 0; --i)
                as_T[i-1].~T();
            
            arena.free(as_size_t-1, info);
        }
        
        template <typename T, class A>
        void delete_array_mem(A& arena, T* ptr, const source_info& info)
        {
            if(ptr)
                delete_array_mem(arena, ptr, info, bool_to_type<std::is_pod<T>::value>());
        }
    }
};

#pragma once

#include <core/types.h>
#include <core/logging/log.h>

#include <cassert>
#include <type_traits>
#include <new>

#define CORE_NEW(arena, type, ...) (new ((arena).allocate(sizeof(type), alignof(type), 0, CORE_SOURCEINFO)) type(__VA_ARGS__))
#define CORE_NEW_ALIGNED(arena, type, alignment, ...) (new ((arena).allocate(sizeof(type), alignment, 0, CORE_SOURCEINFO)) type(__VA_ARGS__))

#define CORE_DELETE(arena, object) core::memory_internals::delete_mem(arena, object, CORE_SOURCEINFO)

#define CORE_NEW_ARRAY(arena, type) core::memory_internals::new_array_mem<core::type_and_count<type>::Type>(arena, core::type_and_count<type>::Count, CORE_SOURCEINFO)

#define CORE_DELETE_ARRAY(arena, ptr) core::memory_internals::delete_array_mem(arena, ptr, CORE_SOURCEINFO);

namespace core
{
    //TODO CORE_NEW_ARRAY_ALIGNED
    namespace memory_internals
    {
        typedef bool_to_type<false> NonPODType;
        typedef bool_to_type<true> PODType;

        template<typename T>
        void destruct(T* object, NonPODType)
        {
                object->~T();
        }

        template<typename T>
        void destruct(T* object, PODType)
        {
            //Do nothing
        }

        template<typename T>
        void destruct(T* object)
        {
            assert(object);

            destruct(object, bool_to_type<std::is_pod<T>::value>());
        }

        template<typename T>
        void destruct_array(T* objects, const size_t N)
        {
            assert(objects);

            for(size_t i=N; i>0; --i)
                destruct(objects + i - 1);
        }

        template<class A, typename T>
        void delete_mem(A& arena, T* object, const source_info& info)
        {
            if(object)
            {
                destruct(object);
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

            as_void = arena.allocate( sizeof(T) * count + sizeof(size_t), alignof(T), sizeof(size_t), info );

            *as_size_t++ = count;

            const T* const end = as_T + count;

            while(as_T < end)
            {
                new (as_T++) T;
            }

            return (as_T - count);
        }

        template<typename T, class A>
        T* new_array_mem(A& arena, size_t count, const source_info& info)
        {
            return new_array_mem<T>(arena, count, info, bool_to_type<std::is_pod<T>::value>());
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

            destruct_array(as_T, count);
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

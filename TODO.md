TODO
====

* Asyncronous file operations on linux, mac and windows
** use tasking library to do blocking I/O behind the scenes
** do _all_ I/O through async. I/O, with different priorities.
** support doing multiple I/O operations at the same time.
* unbuffered flag for files
* replace fstream with FILE* in fs_file.h

* most compile-time stuff in types.h to somewhere else
* compiler.h
** _used, _unused
** _restricted
** _noreturn
** _final
** _override
** _force_inline

* add tasking API
* allow cleanup in thread_local_storage

* code comments
* tests
* test suite
* samples

* sounds more like a libmath thing
** add math/vectory things (vector3,vector2,quaternion,matrix,etc)
** SIMD

* clean up memory.h, add examples, decide what to include
* 'fancy' arena -> memory_arena
** with guards and other features
* write a macro to re-size a size to include the CORE_NEW_ARRAY overhead
* virtual_memory namespace with (reserve, release), (commit, decommit), (alloc and free).
* system_allocator -> alignment
* pool allocator -> http://molecularmusings.wordpress.com/2012/09/17/memory-allocation-strategies-a-pool-allocator/
* more allocators

* {fixed,dynamic}_{queue,hashmap}
* linked list

* SOURCE_GROUP in CMakeLists.txt
* file logger
* profiler

* make fnv1a constexpr dependent on platform

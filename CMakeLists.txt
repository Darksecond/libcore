cmake_minimum_required (VERSION 2.6)
enable_testing ()

project (core)
set (core_VERSION_MAJOR 0)
set (core_VERSION_MINOR 1)

include_directories (include)

#TODO Make this dependent on the compiler used (MSVC vs clang)
if (UNIX)
	set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")
endif ()
if (APPLE)
	set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
endif ()

# Platform dependent files
# Files for all UNIX platforms (things like pthread fit here)
if (UNIX)
	set (PLATFORM_FILES ${PLATFORM_FILES}
		src/core/threading/unix/condition_variable.cc
		src/core/threading/unix/mutex.cc
		src/core/threading/unix/thread.cc
		)
endif ()

# Apple only code, such as mach timers
if (APPLE)
	set (PLATFORM_FILES ${PLATFORM_FILES}
		src/core/time/apple/hf_timer.cc
		)
endif ()

add_library (core
	include/core/hashing/fnv1a.h
	include/core/memory.h
	include/core/platform.h
	include/core/types.h
	include/core/util/union_cast.h
	include/core/util/event.h
	include/core/containers/dynamic_array.h
	include/core/containers/fixed_array.h
	include/core/containers/freelist.h
	include/core/containers/fixed_stack.h
	include/core/containers/dynamic_stack.h
	include/core/filesystem/archive.h
	include/core/filesystem/file.h
	include/core/filesystem/fs_archive.h
	include/core/filesystem/fs_file.h
	include/core/filesystem/modes.h
	include/core/filesystem/root.h
	include/core/logging/console_logger.h
	include/core/logging/log.h
	include/core/memory/arena.h
	include/core/memory/heap_area.h
	include/core/memory/stack_area.h
	include/core/memory/linear_allocator.h
	include/core/memory/new_delete.h
	include/core/memory/simple_arena.h
	include/core/memory/system_allocator.h
	include/core/memory/stack_allocator.h
	include/core/string/fixed_string.h
	include/core/string/string_hash.h
	include/core/threading/condition_variable.h
	include/core/threading/mutex.h
	include/core/threading/thread_local_storage.h
	include/core/threading/thread.h
	include/core/time/hf_timer.h
	include/core/core.h
	include/core/compiler.h
	src/core/filesystem/fs_archive.cc
	src/core/filesystem/fs_file.cc
	src/core/filesystem/root.cc
	src/core/logging/console_logger.cc
	src/core/logging/log.cc
	src/core/memory/heap_area.cc
	src/core/memory/linear_allocator.cc
	src/core/memory/system_allocator.cc
	src/core/memory/stack_allocator.cc
	${PLATFORM_FILES}
	)

add_executable (core_test test/core/core_test.cc)
target_link_libraries (core_test core)
add_test (NAME core_test COMMAND core_test)

install (TARGETS core
	ARCHIVE DESTINATION lib
	LIBRARY DESTINATION lib
	)

install (DIRECTORY include/
	DESTINATION include
	FILES_MATCHING PATTERN "*.h"
	)

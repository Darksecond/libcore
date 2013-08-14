#include <core/filesystem/fs_archive.h>
#include <core/filesystem/fs_file.h>
#include <core/memory/arena.h>
#include <core/memory/new_delete.h>
#include <core/string/fixed_string.h>

#include <sys/stat.h>
#include <cassert>

core::fs_archive::fs_archive(const char* directory, arena* arena) : _arena(arena), _directory(directory)
{
}

core::file* core::fs_archive::open(const char* path, int mode)
{
    fixed_string<512> full_path(_directory);
    full_path.append("/");
    full_path.append(path);
    
    struct stat buffer;
    bool exists = stat(full_path.c_str(), &buffer) == 0;
    if(exists)
        return P_NEW(*_arena, fs_file, full_path.c_str(), mode, this);
    else
        return nullptr;
}

void core::fs_archive::close(file* file)
{
    assert(file);
    
    P_DELETE(*_arena, file);
}

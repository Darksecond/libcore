#include <core/filesystem/root.h>
#include <core/filesystem/archive.h>
#include <core/filesystem/file.h>

#include <cassert>

core::root::root(arena* arena, int capacity) : _mounts(arena, capacity)
{
}

void core::root::mount(archive* archive)
{
    _mounts.add(archive);
}

void core::root::unmount(archive* archive)
{
    _mounts.erase(archive);
}

core::file* core::root::open(const char* path, int mode)
{
    file* retval = nullptr;
    for(archive* mount : _mounts)
    {
        retval = mount->open(path, mode);
        if(retval)
            break;
    }
    return retval;
}

void core::root::close(file* file)
{
    assert(file);
    
    file->owner()->close(file);
}

#include <core/threading/mutex.h>


core::mutex::mutex() : _mutex(PTHREAD_MUTEX_INITIALIZER)
{
}

core::mutex::~mutex()
{
    pthread_mutex_destroy(&_mutex);
}

void core::mutex::lock()
{
    pthread_mutex_lock(&_mutex);
}

bool core::mutex::try_lock()
{
    return pthread_mutex_trylock(&_mutex) == 0;
}

void core::mutex::unlock()
{
    pthread_mutex_unlock(&_mutex);
}

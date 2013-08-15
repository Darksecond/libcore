#include <core/threading/condition_variable.h>
#include <core/threading/mutex.h>

core::condition_variable::condition_variable() : _condition(PTHREAD_COND_INITIALIZER)
{
}

core::condition_variable::~condition_variable()
{
    pthread_cond_destroy(&_condition);
}

void core::condition_variable::signal_one()
{
    pthread_cond_signal(&_condition);
}

void core::condition_variable::signal_all()
{
    pthread_cond_broadcast(&_condition);
}

void core::condition_variable::wait(mutex& m)
{
    pthread_cond_wait(&_condition, &m.os_mutex());
}

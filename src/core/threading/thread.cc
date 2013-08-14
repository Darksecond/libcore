#include <core/threading/thread.h>

#include <cassert>

using namespace core;

thread::thread()
{
    _state = state_t::READY;
}

thread::~thread()
{
    destroy();
}

void thread::create(const char* name, function f)
{
    assert(name != nullptr);
    assert(f != nullptr);
    
    _function = f;
    _name = name;
    int rc = pthread_create(&_thread, nullptr, &thread_main_function, this);
    assert(rc == 0);
    _state = state_t::RUNNING;
}

void thread::destroy()
{
    stop();
    join();
}

void thread::join()
{
    if(_state == state_t::RUNNING || _state == state_t::SHOULD_STOP)
    {
        int rc = pthread_join(_thread, nullptr);
        assert(rc == 0);
    }
}

void thread::stop()
{
    if(_state == state_t::RUNNING)
        _state = state_t::SHOULD_STOP;
}

bool thread::should_stop() const
{
    return _state == state_t::SHOULD_STOP;
}

bool thread::continue_running() const
{
    return !should_stop();
}

bool thread::is_stopped() const
{
    return _state == state_t::STOPPED;
}

void thread::yield()
{
    pthread_yield_np();
}

void* thread::thread_main_function(void* t)
{
    thread* current_thread = static_cast<thread*>(t);
    pthread_setname_np(current_thread->_name);
    current_thread->_function(*current_thread);
    current_thread->_state = state_t::STOPPED;
    
    return nullptr;
}

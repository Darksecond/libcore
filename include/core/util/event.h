#pragma once

#include <core/containers/dynamic_array.h>

namespace core
{
    template<typename T>
        class event;

    template<typename R, typename... Args>
        class event<R (Args...)> {
            typedef R (*ptr)(void*, Args...);

            struct stub
            {
                void* instance;
                ptr function;

                inline bool operator==(const stub& other)
                {
                    return (instance == other.instance) && (function == other.function);
                }
            };

            template<class T, R (T::*Function)(Args...)>
                static R class_method_stub(void* instance, Args... args)
                {
                    return (static_cast<T*>(instance)->*Function)(args...);
                }

            template<class T, R (T::*Function)(Args...) const>
                static R const_class_method_stub(void* instance, Args... args)
                {
                    return (static_cast<const T*>(instance)->*Function)(args...);
                }

            template<R (*Function)(Args...)>
                static R function_stub(void* instance, Args... args)
                {
                    return (Function)(args...);
                }
        public:
            event() : _sink(nullptr)
            {
            }

            class sink
            {
                core::dynamic_array<stub> stubs;
                friend class event;
            public:

                    sink(arena* a, const int max_listeners) : stubs(a, max_listeners)
                    {
                    }

                    //Non-const class member
                    template<class T, R (T::*Function)(Args...)>
                        void add_listener(T* o) {
                            stub stub;
                            stub.instance = o;
                            stub.function = &class_method_stub<T, Function>;
                            stubs.add(stub);
                        }

                    //const class member
                    template<class T, R (T::*Function)(Args...) const>
                        void add_listener(T* o) {
                            stub stub;
                            stub.instance = o;
                            stub.function = &const_class_method_stub<T, Function>;
                            stubs.add(stub);
                        }

                    //Freestanding function
                    template<R (*Function)(Args...)>
                        void add_listener() {
                            stub stub;
                            stub.instance = nullptr;
                            stub.function = &function_stub<Function>;
                            stubs.add(stub);
                        }

                    //Non-const class member
                    template<class T, R (T::*Function)(Args...)>
                        void remove_listener(T* o) {
                            stub stub;
                            stub.instance = o;
                            stub.function = &class_method_stub<T, Function>;
                            stubs.erase(stub);
                        }

                    //const class member
                    template<class T, R (T::*Function)(Args...) const>
                        void remove_listener(T* o) {
                            stub stub;
                            stub.instance = o;
                            stub.function = &const_class_method_stub<T, Function>;
                            stubs.erase(stub);
                        }

                    //Freestanding function
                    template<R (*Function)(Args...)>
                        void remove_listener() {
                            stub stub;
                            stub.instance = nullptr;
                            stub.function = &function_stub<Function>;
                            stubs.erase(stub);
                        }
            };

            void bind(sink* sink)
            {
                _sink = sink;
            }

            /**
             * Signal all the listeners in the bound sink.
             * This will assert if no sink is bound, use is_bound() to check.
             */
            //TODO Do something with the return values perhaps?
            void signal(Args... args) const
            {
                assert(is_bound());
                for(int i=0;i<_sink->stubs.size();++i)
                {
                    const stub& stub = _sink->stubs[i];
                    stub.function(stub.instance, args...);
                }

            }

            bool is_bound() const
            {
                return _sink != nullptr;
            }
        private:
            sink* _sink;
        };
}

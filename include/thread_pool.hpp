#ifndef THREAD_POOL_HPP
#define THREAD_POOL_HPP

#include <vector>
#include <thread>
#include <queue>
#include <functional>
#include <mutex>
#include <condition_variable>
#include <future>
#include <atomic>

class thread_pool {
    public:
        thread_pool( size_t thread_count ) : stop_flag( false ) {
            for ( size_t i = 0; i < thread_count; ++i ) {
                workers.emplace_back( [ this ]() {
                    while ( true ) {
                        std::function<void()> task;

                        // lock the queue to retrieve a task
                        {
                            std::unique_lock<std::mutex> lock( queue_mutex );
                            condition.wait( lock, [ this ]() { return stop_flag || !tasks.empty(); } );

                            if ( stop_flag && tasks.empty() ) {
                                return; // exit the thread
                            }

                            task = std::move( tasks.front() );
                            tasks.pop();
                        }

                        // execute the task
                        task();
                    }
                });
            }
        }

        // submit a task to the pool
        template<typename F, typename... Args>
        auto enqueue( F&& f, Args&&... args ) -> std::future<typename std::invoke_result<F, Args...>::type> {
            using return_type = typename std::invoke_result<F, Args...>::type;

            auto task = std::make_shared<std::packaged_task<return_type()>>(
                std::bind( std::forward<F>( f ), std::forward<Args>( args )... )
            );

            std::future<return_type> result = task->get_future();
            {
                std::lock_guard<std::mutex> lock( queue_mutex );
                tasks.emplace( [ task ]() { ( *task )(); } );
            }

            condition.notify_one();
            return result;
        }

        // destructor: join all threads
        ~thread_pool() {
            {
                std::lock_guard<std::mutex> lock( queue_mutex );
                stop_flag = true;
            }

            condition.notify_all();
            for ( std::thread& worker : workers ) {
                if ( worker.joinable() ) {
                    worker.join();
                }
            }
        }

    private:
        std::vector<std::thread> workers;
        std::queue<std::function<void()>> tasks;

        std::mutex queue_mutex;
        std::condition_variable condition;
        std::atomic<bool> stop_flag;
};

#endif

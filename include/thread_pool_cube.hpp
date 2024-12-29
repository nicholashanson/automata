#ifndef THREAD_POOL_CUBE_HPP
#define THREAD_POOL_CUBE_HPP

#include <vector>
#include <future>

#include <cube.hpp>
#include <thread_pool.hpp>

namespace conway {

    template<typename array, typename mdspan>
    class thread_pool_cube : public cube<array, mdspan> {
        public:
            using cube<array, mdspan>::cube;

            thread_pool_cube( array cells )
                : cube<array, mdspan>( cells ), thread_pool_( 12 ) {}

            void evolve_faces() override {

                std::vector<std::future<void>> futures;

                // submit tasks to the thread pool for each face
                for ( auto& face : this->faces ) {
                    futures.push_back( thread_pool_.enqueue( [ &face ]() {
                        evolve( face );
                    } ) );
                }

                // wait for all tasks to complete
                for ( auto& future: futures ) {
                    future.get();
                }
            }

        private:
            thread_pool thread_pool_;
    };

}

#endif

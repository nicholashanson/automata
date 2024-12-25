#ifndef THREADED_CUBE_HPP
#define THREADED_CUBE_HPP

#include <thread>
#include <vector>

#include <cube.hpp>

namespace conway {

    template<typename array, typename mdspan>
    class threaded_cube : public cube<array, mdspan> {

        public:

            using cube<array, mdspan>::cube;

            void evolve_faces() override {
                std::vector<std::thread> threads;

                for ( auto& face: this->faces ) {
                    threads.emplace_back( [ &face ]() {
                        evolve( face );
                    });
                }

                for ( auto& thread : threads ) {
                    if ( thread.joinable() ) {
                        thread.join();
                    }
                }
            }

    };

}

#endif

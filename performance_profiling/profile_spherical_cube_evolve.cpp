#include <performance_profile.hpp>

#include <conway.hpp>

using namespace conway;

const size_t iterations = 200;
const size_t runs = 1;

using base_fixture = profiler::base_fixture<iterations, runs>;

struct cube_fixture : base_fixture {
    cube_fixture()
        : cube( cell_states ) {    
    };

    cube<sim_array, sim_mdspan> cube;
};

struct tc_fixture : base_fixture {
    tc_fixture() 
        : tc( cell_states ) {
    }; 

    threaded_cube<sim_array, sim_mdspan> tc;
};

struct tpc_fixture : base_fixture { 
    tpc_fixture() 
        : tpc( cell_states ) {
    };

    thread_pool_cube<sim_array, sim_mdspan> tpc;
};

PROFILE_AVG( cube, spherical_cube_evolve, cube_fixture, {

    START_TIMER
    fx.cube.evolve_faces();
    END_TIMER

    fx.cube.update_faces();
})

PROFILE_AVG( threaded_cube, spherical_cube_evolve, tc_fixture, {

    START_TIMER
    fx.tc.evolve_faces();
    END_TIMER

    fx.tc.update_faces();
})

PROFILE_AVG( thread_pool_cube, spherical_cube_evolve, tpc_fixture, {

    START_TIMER
    fx.tpc.evolve_faces();
    END_TIMER

    fx.tpc.update_faces();
})
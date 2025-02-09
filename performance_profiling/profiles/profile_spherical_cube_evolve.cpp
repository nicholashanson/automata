#include <performance_profile.hpp>

#include <conway.hpp>

using namespace conway;

const size_t iterations = 400;
const size_t runs = 10;

using base_fixture_sce = profiler::base_fixture<iterations, runs>;

struct cube_fixture_sce : base_fixture_sce {
    cube_fixture_sce()
        : cube( cell_states ) {    
    };

    cube<sim_array, sim_mdspan> cube;
};

struct tc_fixture_sce : base_fixture_sce {
    tc_fixture_sce() 
        : tc( cell_states ) {
    }; 

    threaded_cube<sim_array, sim_mdspan> tc;
};

struct tpc_fixture_sce : base_fixture_sce { 
    tpc_fixture_sce() 
        : tpc( cell_states ) {
    };

    thread_pool_cube<sim_array, sim_mdspan> tpc;
};

PROFILE( cube, spherical_cube_evolve, cube_fixture_sce, {

    START_TIMER
    fx.cube.evolve_faces();
    END_TIMER

    fx.cube.update_faces();
})

PROFILE( threaded_cube, spherical_cube_evolve, tc_fixture_sce, {

    START_TIMER
    fx.tc.evolve_faces();
    END_TIMER

    fx.tc.update_faces();
})

PROFILE( thread_pool_cube, spherical_cube_evolve, tpc_fixture_sce, {

    START_TIMER
    fx.tpc.evolve_faces();
    END_TIMER

    fx.tpc.update_faces();
})

GENERATE_GRAPH( spherical_cube_evolve )
#define PERFORMANCE_PROFILE_MAIN
#include <performance_profile.hpp>

#include <conway.hpp>

using namespace conway;

struct f : profiler::base_fixture<100,10> {

    f() : bd( cell_states ) {
        seed( bd );
    }

    board<sim_array, sim_mdspan> bd;
};

PROFILE_AVG( basic_evolve, evolve, f, {

    START_TIMER
    evolve( fx.bd );
    END_TIMER

    update_padding( fx.bd );
})


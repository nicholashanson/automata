#include <performance_profile.hpp>

#include <conway.hpp>

using namespace conway;

using base_fixture_e = profiler::base_fixture<400, 10>;

struct board_fixture_e : base_fixture_e {

    board_fixture_e() : bd( cell_states ) {
        seed( bd );
    }

    board<sim_array, sim_mdspan> bd;
};

struct set_fixture_e : base_fixture_e {

    set_fixture_e() : bd( cell_states ) {
        seed( bd );
    }

    board_set<sim_array, sim_mdspan> bd;
};

struct unordered_set_fixture_e : base_fixture_e {

    unordered_set_fixture_e() : bd( cell_states ) {
        seed( bd );
    }

    board_unordered_set_xor<sim_array, sim_mdspan> bd;
};

PROFILE( board, evolve, board_fixture_e, {

    START_TIMER
    evolve( fx.bd );
    END_TIMER

    update_padding( fx.bd );
})

PROFILE( set, evolve, set_fixture_e, {

    START_TIMER
    optimised_evolve_( fx.bd );
    END_TIMER

    update_padding( fx.bd );
})

PROFILE( unordered_set, evolve, unordered_set_fixture_e, {

    START_TIMER
    optimised_evolve_( fx.bd );
    END_TIMER

    update_padding( fx.bd );
})

GENERATE_GRAPH( evolve )
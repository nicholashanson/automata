#include <performance_profile.hpp>

#include <conway.hpp>

using namespace conway;

using base_fixture_sh = profiler::base_fixture<400, 10>;

struct board_fixture_sh : base_fixture_sh {

    board_fixture_sh() : bd( cell_states ) {
        seed( bd );
    }

    board<sim_array, sim_mdspan> bd;
};

struct xor_hash_fixture_sh : base_fixture_sh {

    xor_hash_fixture_sh() : bd( cell_states ) {
        seed( bd );
    }

    board_unordered_set_xor<sim_array, sim_mdspan> bd;
};

struct perfect_hash_fixture_sh : base_fixture_sh {

    perfect_hash_fixture_sh() : bd( cell_states ) {
        seed( bd );
    }

    board_unordered_set_perfect<sim_array, sim_mdspan> bd;
};

PROFILE( board, set_hash, board_fixture_sh, {

    START_TIMER
    evolve( fx.bd );
    END_TIMER

    update_padding( fx.bd );
})

PROFILE( xor_hash, set_hash, xor_hash_fixture_sh, {

    START_TIMER
    optimised_evolve_( fx.bd );
    END_TIMER

    update_padding( fx.bd );
})

PROFILE( pefect_hash, set_hash, perfect_hash_fixture_sh, {

    START_TIMER
    optimised_evolve_( fx.bd );
    END_TIMER

    update_padding( fx.bd );
})

GENERATE_GRAPH( set_hash )
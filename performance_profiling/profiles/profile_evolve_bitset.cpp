#define PERFORMANCE_PROFILE_MAIN
#include <performance_profile.hpp>

#include <conway.hpp>

using namespace conway;

using base_fixture_eb = profiler::base_fixture<400, 40>;

struct board_fixture_eb : base_fixture_eb {

    board_fixture_eb() : bd( cell_states ) {
        seed( bd );
    }

    board<sim_array, sim_mdspan> bd;
};

struct perfect_hash_fixture_eb : base_fixture_eb {

    perfect_hash_fixture_eb() : bd( cell_states ) {
        seed( bd );
    }

    board_unordered_set_perfect<sim_array, sim_mdspan> bd;
};

struct bitset_fixture_eb : base_fixture_eb {

    bitset_fixture_eb() : bd( cell_states ) {
        seed( bd );
    }

    board_bitset<sim_array, sim_mdspan> bd;
};

PROFILE( board, evolve_bitset, board_fixture_eb, {

    START_TIMER
    evolve( fx.bd );
    END_TIMER

    update_padding( fx.bd );
})

PROFILE( perfect_hash, evolve_bitset, perfect_hash_fixture_eb, {

    START_TIMER
    optimised_evolve_( fx.bd );
    END_TIMER

    update_padding( fx.bd );
})

PROFILE( bitset, evolve_bitset, bitset_fixture_eb, {

    START_TIMER
    evolve_bitset( fx.bd );
    END_TIMER

    update_padding( fx.bd );
})

GENERATE_GRAPH( evolve_bitset )
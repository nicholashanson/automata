#include <boost/test/unit_test.hpp>
#include "conway.hpp"

using namespace conway;

BOOST_AUTO_TEST_CASE( EvolveTest )
{
    board<sim_array, sim_mdspan> bd( cell_states );

    seed( bd );

    board_set<sim_array, sim_mdspan> bd_set;
    board_unordered_set_xor<sim_array, sim_mdspan> bd_xor;
    board_unordered_set_perfect<sim_array, sim_mdspan> bd_perfect;
    board_bitset<sim_array, sim_mdspan> bd_bitset;

    bd_set = bd;
    bd_xor = bd;
    bd_perfect = bd;
    bd_bitset = bd;

    evolve( bd );
    evolve_set( bd_set );
    evolve_set( bd_xor );
    evolve_set( bd_perfect );
    evolve_bitset( bd_bitset );
    
    BOOST_CHECK( ( bd == bd_set ) );
    BOOST_CHECK( ( bd == bd_xor ) );
    BOOST_CHECK( ( bd == bd_perfect ) );
    BOOST_CHECK( ( bd == bd_bitset ) );
}

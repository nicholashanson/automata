#include <boost/test/unit_test.hpp>
#include "conway.hpp"

using namespace conway;

/*
    Rule one: Any live cell with fewer than two live neighbors dies,
    as if by underpopulation.
*/

// cell dies with zero live neighbors
BOOST_AUTO_TEST_CASE( RuleOneTest_0_set )
{
    board_set<a25, md5x5> bd( rule_one_0_before );
    evolve_set( bd );
    BOOST_CHECK( ( bd == board_set<a25, md5x5>( rule_one_0_after ) ) );
}

// cell dies with one live neighbor
BOOST_AUTO_TEST_CASE( RuleOneTest_1_set )
{
    board_set<a25, md5x5> bd( rule_one_1_before );
    evolve_set( bd );
    BOOST_CHECK( ( bd == board_set<a25, md5x5>( rule_one_1_after ) ) );
}

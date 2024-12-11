#include <boost/test/unit_test.hpp>
#include "conway.hpp"

/*
    Rule one: Any live cell with fewer than two live neighbors dies,
    as if by underpopulation.
*/

// cell dies with zero live neighbors
BOOST_AUTO_TEST_CASE( RuleOneTest_0 )
{
    conway::board<conway::a25, conway::md5x5> bd( conway::rule_one_0_before );
    conway::evolve( bd );
    BOOST_CHECK( ( bd == conway::board<conway::a25, conway::md5x5>( conway::rule_one_0_after ) ) );
}

// cell dies with one live neighbor
BOOST_AUTO_TEST_CASE( RuleOneTest_1 )
{
    conway::board<conway::a25, conway::md5x5> bd( conway::rule_one_1_before );
    conway::evolve( bd );
    BOOST_CHECK( ( bd == conway::board<conway::a25, conway::md5x5>( conway::rule_one_1_after ) ) );
}

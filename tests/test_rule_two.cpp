#include <boost/test/unit_test.hpp>
#include "conway.hpp"

/*
    Rule two: Any live cell with two or three live neighbors lives
    on to the next generation.
*/

// cell survives with two live cells
BOOST_AUTO_TEST_CASE( RuleTwo_2_Test )
{
    conway::conway_board_2d<conway::a25, conway::md5x5> bd( conway::rule_two_2_before );
    conway::optimised_evolve( bd );
    BOOST_CHECK( ( bd == conway::conway_board_2d<conway::a25, conway::md5x5>( conway::rule_two_2_after ) ) );
}

// cell survives with three live cells
BOOST_AUTO_TEST_CASE( RuleTwo_3_Test )
{
    conway::conway_board_2d<conway::a49, conway::md7x7> bd( conway::rule_two_3_before );
    conway::optimised_evolve( bd );
    BOOST_CHECK( ( bd == conway::conway_board_2d<conway::a49, conway::md7x7>( conway::rule_two_3_after ) ) );
}

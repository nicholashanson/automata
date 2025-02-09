#include <boost/test/unit_test.hpp>
#include "conway.hpp"

using namespace conway;

/*
    Rule two: Any live cell with two or three live neighbors lives
    on to the next generation.
*/

// cell survives with two live cells
BOOST_AUTO_TEST_CASE( RuleTwo_2_Test )
{
    board<a25, md5x5> bd( rule_two_2_before );
    evolve( bd );
    BOOST_CHECK( ( bd == board<a25, md5x5>( rule_two_2_after ) ) );
}

// cell survives with three live cells
BOOST_AUTO_TEST_CASE( RuleTwo_3_Test )
{
    board<a49, md7x7> bd( rule_two_3_before );
    evolve( bd );
    BOOST_CHECK( ( bd == board<a49, md7x7>( rule_two_3_after ) ) );
}

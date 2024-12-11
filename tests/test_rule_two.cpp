#include <boost/test/unit_test.hpp>
#include "conway.h"

/*
    Rule two: Any live cell with two or three live neighbors lives
    on to the next generation.
*/

// cell survives with two live cells
BOOST_AUTO_TEST_CASE( RuleTwo_2_Test )
{
    conway::board<conway::a25, conway::md5x5> bd( conway::rule_two_2_before );
    conway::evolve( bd );
    BOOST_CHECK( ( bd == conway::board<conway::a25, conway::md5x5>( conway::rule_two_2_after ) ) );
}

// cell survives with three live cells
BOOST_AUTO_TEST_CASE( RuleTwo_3_Test )
{
    conway::board<conway::a49, conway::md7x7> bd( conway::rule_two_3_before );
    conway::evolve( bd );
    BOOST_CHECK( ( bd == conway::board<conway::a49, conway::md7x7>( conway::rule_two_3_after ) ) );
}

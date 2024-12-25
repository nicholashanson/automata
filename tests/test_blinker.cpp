#include <boost/test/unit_test.hpp>
#include "conway.hpp"

BOOST_AUTO_TEST_CASE( BlinkerTest )
{
    conway::board<conway::a49, conway::md7x7> bd( conway::blinker_period_0 );
    conway::evolve( bd );
    BOOST_CHECK( ( bd == conway::board<conway::a49, conway::md7x7>( conway::blinker_period_1 ) ) );
}


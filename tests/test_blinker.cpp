#include <boost/test/unit_test.hpp>
#include "conway.hpp"

using namespace conway;

BOOST_AUTO_TEST_CASE( BlinkerTest )
{
    board<a49, md7x7> bd( blinker_period_0 );
    evolve( bd );
    BOOST_CHECK( ( bd == board<a49, md7x7>( blinker_period_1 ) ) );
}
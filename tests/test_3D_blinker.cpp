#include <boost/test/unit_test.hpp>
#include "conway.hpp"

using namespace conway;

BOOST_AUTO_TEST_CASE( 3DBlinkerTest )
{
    toroidal_cube<board<a49, md7x7>> tc( blank_a49,
                                         blank_a49,
                                         blinker_period_0,
                                         blank_a49
                                         blank_a49 );
    tc.evolve();
    BOOST_CHECK( ( tc.get_plane<0,0> == board<a49, md7x7>( blinker_period_1 ) ) );
}

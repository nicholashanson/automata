#include <boost/test/unit_test.hpp>
#include "conway.hpp"

using namespace conway;

BOOST_AUTO_TEST_CASE( Blinker3DTest )
{
    toroidal_cube<a49, md7x7, board, 5> tc( blank_a49,
                                            blank_a49,
                                            blinker_period_0,
                                            blank_a49,
                                            blank_a49 );
    tc.evolve_cube();
    BOOST_CHECK( tc.equal_boards<0>( 3, board<a49, md7x7>( blank_a49 ) ) );
}

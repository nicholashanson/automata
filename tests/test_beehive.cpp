#include <boost/test/unit_test.hpp>
#include "conway.hpp"

BOOST_AUTO_TEST_CASE( BeehiveTest )
{
    conway::board<conway::a56, conway::md7x8> bd( conway::beehive );
    conway::evolve( bd );
    BOOST_CHECK( ( bd == conway::board<conway::a56, conway::md7x8>( conway::beehive ) ) );
}

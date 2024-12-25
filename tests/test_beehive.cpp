#include <boost/test/unit_test.hpp>
#include "conway.hpp"

using namespace conway;

BOOST_AUTO_TEST_CASE( BeehiveTest )
{
    board<a56, md7x8> bd( beehive );
    evolve( bd );
    BOOST_CHECK( ( bd == board<a56, md7x8>( beehive ) ) );
}

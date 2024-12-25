#include <boost/test/unit_test.hpp>
#include "conway.hpp"

using namespace conway;

BOOST_AUTO_TEST_CASE( BlockTest )
{
    board<a36, md6x6> bd( block );
    evolve( bd );
    BOOST_CHECK( ( bd == board<a36, md6x6>( block ) ) );
}

#include <boost/test/unit_test.hpp>
#include "conway.h"

BOOST_AUTO_TEST_CASE( BlockTest )
{
    conway::board<conway::a36, conway::md6x6> bd( conway::block );
    conway::evolve( bd );
    BOOST_CHECK( ( bd == conway::board<conway::a36, conway::md6x6>( conway::block ) ) );
}

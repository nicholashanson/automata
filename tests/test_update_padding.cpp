#include <boost/test/unit_test.hpp>
#include "conway.hpp"

BOOST_AUTO_TEST_CASE( UpdatePaddingTest )
{
    conway::board<conway::a49, conway::md7x7> bd( conway::board_update_before );
    conway::update_padding( bd );
    BOOST_CHECK( ( bd == conway::board<conway::a49, conway::md7x7>( conway::board_update_after ) ) );
}

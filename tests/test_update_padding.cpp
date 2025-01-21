#include <boost/test/unit_test.hpp>
#include "conway.hpp"

using namespace conway;

BOOST_AUTO_TEST_CASE( UpdatePaddingTest )
{
    board<a49, md7x7> bd( board_update_before );
    update_padding( bd );
    BOOST_CHECK( ( bd == board<a49, md7x7>( board_update_after ) ) );
}

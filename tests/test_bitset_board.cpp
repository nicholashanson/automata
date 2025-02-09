#include <boost/test/unit_test.hpp>
#include "conway.hpp"

using namespace conway;

BOOST_AUTO_TEST_CASE( BitsetBoardTest )
{
    board_bitset<a49, md7x7> bd( blinker_period_0 );

    BOOST_CHECK( bd.cell_count() == 25 );
    evolve_bitset( bd );
    BOOST_CHECK( bd.cell_count() == 15 );
}

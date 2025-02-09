#include <boost/test/unit_test.hpp>
#include "conway.hpp"

using namespace conway;

BOOST_AUTO_TEST_CASE( ActiveCellsOptimizationTest )
{
    board_set<a49, md7x7> bd( blinker_period_0 );

    /*
        all cells in the board are in the set "active_cells"
    */
    BOOST_CHECK( bd.cell_count() == 25 ); // 49 cells - padding = 25

    evolve_set( bd );

    /*
        only those cells with no a non-zero region-live-count are in the set active_cells

        board configuration:        region live count:
        0 0 0 0 0                   0 0 0 0 0
        0 0 0 0 0                   1 2 3 2 1
        0 1 1 1 0                   1 2 3 2 1
        0 0 0 0 0                   1 2 3 2 1
        0 0 0 0 0                   0 0 0 0 0

    */
    // fifteen cells with a non-zero region-live-count
    BOOST_CHECK( bd.cell_count() == 15 );
}


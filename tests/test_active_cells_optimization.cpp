#include <boost/test/unit_test.hpp>
#include "conway.hpp"

BOOST_AUTO_TEST_CASE( ActiveCellsOptimizationTest )
{
    conway::conway_board_2d<conway::a49, conway::md7x7> bd( conway::blinker_period_0 );

    /*
        all cells in the board are in active_cells
    */
    BOOST_CHECK( bd.cell_count() == 25 ); // 49 cells - padding = 25

    conway::optimised_evolve( bd );

    /*
        only those cells with no a non-zero region live count are in active cells

        board configuration:        region live count:
        0 0 0 0 0                   0 0 0 0 0
        0 0 0 0 0                   1 2 3 2 1
        0 1 1 1 0                   1 2 3 2 1
        0 0 0 0 0                   1 2 3 2 1
        0 0 0 0 0                   0 0 0 0 0

    */
    // fifteen cell with a non-zero region live count
    BOOST_CHECK( bd.cell_count() == 15 );

}


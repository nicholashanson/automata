#ifndef UPDATE_PADDING_HPP
#define UPDATE_PADDING_HPP

namespace conway {

    // toroidal wrapping
    template<typename array, typename mdspan>
    void update_padding( board<array, mdspan>& bd ) {
        // indexes for columns and rows
        size_t bottom_padding = bd.get_board_height() - 1;
        size_t bottom_index = bd.get_board_height() - 2;
        size_t right_padding = bd.get_board_width() - 1;
        size_t right_index = bd.get_board_width() - 2;

        // update top and bottom row padding
        for ( size_t column = 0; column < bd.get_board_width(); column++ ) {
            bd.set_cell_state( 0, column, bd.get_cell_state( bottom_index, column ) );
            bd.set_cell_state( bottom_padding, column, bd.get_cell_state( 1, column ) );
        }

        // update left and right column padding
        for ( size_t row = 0; row < bd.get_board_height(); row++ ) {
            bd.set_cell_state( row, 0, bd.get_cell_state( row, right_index ) );
            bd.set_cell_state( row, right_padding, bd.get_cell_state( row, 1 ) );
        }
    }

}

#endif

#ifndef SEED_HPP
#define SEED_HPP

namespace conway {

    // random seed
    template<typename array, typename mdspan>
    void seed( board<array, mdspan>& bd ) {
        // generator for random state
        std::random_device rd;
        std::default_random_engine generator( rd() );
        std::uniform_int_distribution<int> distribution( 0, 1 );

        // assign random state to every cell in board
        // excluding padding
        for ( size_t i = 1; i < bd.get_board_height() - 1; ++i )
            for ( size_t j = 1; j < bd.get_board_width() - 1; ++j )
                bd.set_cell_state( i, j, distribution( generator ) );
    }

}

#endif

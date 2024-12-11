#ifndef EVOLVE_HPP
#define EVOLVE_HPP

namespace conway {

    template<typename array, typename mdspan>
    void evolve( board<array, mdspan>& bd ) {
        // new state
        array new_cell_states;
        std::ranges::copy( bd.cell_states_, new_cell_states.begin() );
        mdspan new_board( new_cell_states.data() );

        // loop through cells, excluding edge cells
        for ( size_t i = 1; i < bd.board_.static_extent( 0 ) - 1; i++ )
            for ( size_t j = 1; j < bd.board_.static_extent( 1 ) - 1; j++ ) {
                unsigned region_live_count{};

                // loop nine-cell region
                for ( int k = -1; k <= 1; k++ )
                    for ( int l = -1; l <= 1; l++ )
                        // if cell is live, increment live-cell count
                        if ( bd.board_[ i + k, j + l ] == 1 )
                            region_live_count++;

                // apply rules
                if ( region_live_count == 3 )
                    new_board[ i, j ] = 1;
                else if ( region_live_count == 4 )
                    continue;
                else
                    new_board[ i, j ] = 0;
            }

        // reassign state
        bd.cell_states_ = std::move( new_cell_states );
        bd.board_ = mdspan( bd.cell_states_.data() );
    }

}

#endif

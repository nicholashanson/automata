#ifndef EVOLVE_HPP
#define EVOLVE_HPP

namespace conway {

    using live_count = std::tuple<size_t, size_t, unsigned>;

    // evolve the board according to game of life rules
    template<typename array, typename mdspan>
    void evolve( board<array, mdspan>& bd ) {

        std::vector<live_count> region_live_counts;
        region_live_counts.reserve( bd.get_board_height() * bd.get_board_width() );

        get_region_live_counts( bd, region_live_counts );

        apply_rules( bd, region_live_counts );
    }

    // get the live counts for each nine-cell region on the board
    template<typename array, typename mdspan>
    void get_region_live_counts( const board<array, mdspan>& bd, std::vector<live_count>& region_live_counts ) {

        // loop through cells, excluding edge cells
        for ( size_t i = 1; i < bd.get_board_height() - 1; ++i )
            for ( size_t j = 1; j < bd.get_board_width() - 1; ++j ) {

                unsigned region_live_count{};

                region_live_count = get_region_live_count( bd, i, j );

                region_live_counts.emplace_back( live_count{ i, j, region_live_count } );
            }
    }

    template<typename array, typename mdspan>
    void apply_rules( board<array, mdspan>& bd, const std::vector<live_count>& region_live_counts ) {

        std::ranges::for_each( region_live_counts, [&]( const auto& region_live_count ){

            // apply rules
            auto [ i, j, live_count ] = region_live_count;

            if ( live_count == 3 ) // live cell survives, dead cell comes to life
                bd.set_cell_state( i, j, 1 );

            else if ( live_count == 4 ) // cell maintains its status
                return;

            else // cell dies
                bd.set_cell_state( i, j, 0 );
        } );

    }

    // count the number of lives cells in a nine-cell region
    template<typename array, typename mdspan>
    unsigned get_region_live_count( const board<array, mdspan>& bd, const size_t i, const size_t j ) {

        unsigned region_live_count{};

        // loop nine-cell region
        for ( int di = -1; di <= 1; ++di )
            for ( int dj = -1; dj <= 1; ++dj )

                // if cell is live, increment live-cell count
                if ( bd.get_cell_state( i + di, j + dj ) == 1 )
                    region_live_count++;

        return region_live_count;
    }

}

#endif

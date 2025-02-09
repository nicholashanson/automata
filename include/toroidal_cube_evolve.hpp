#ifndef TOROIDAL_CUBE_EVOLVE_HPP
#define TOROIDAL_CUBE_EVOLVE_HPP

namespace conway {

    namespace toroidal_cube_evolve {

        using live_count = std::tuple<size_t, size_t, unsigned>;

        template<typename array, typename mdspan, size_t cube_rank>
        unsigned get_region_live_count( std::array<board<array, mdspan>, cube_rank + 2>& slices,
                                        const size_t slice, const size_t i, const size_t j ) {

            unsigned region_live_count{};

            for ( int dk = -1; dk <= 1; dk++ )
                for ( int di = -1; di <= 1; di++ )
                    for ( int dj = -1; dj <= 1; dj++ )

                        if ( slices[ slice + dk ].get_cell_state( i + di, j + dj ) == 1 )
                            region_live_count++;

            return region_live_count;
        }

        // get the live counts for each nine-cell region on the board
        template<typename array, typename mdspan, size_t cube_rank>
        void get_region_live_counts( std::array<board<array, mdspan>, cube_rank + 2>& slices,
                                     const size_t slice, std::vector<live_count>& region_live_counts ) {

            const size_t board_height = slices[ slice ].get_board_height() - 1;
            const size_t board_width = slices[ slice ].get_board_width() - 1;

            // loop through cells, excluding edge cells
            for ( size_t i = 1; i < board_height; ++i )
                for ( size_t j = 1; j < board_width; ++j ) {

                    unsigned region_live_count{};

                    region_live_count = get_region_live_count<array, mdspan, cube_rank>( slices, slice, i, j );

                    region_live_counts.emplace_back( live_count{ i, j, region_live_count } );
            }
        }

        template<typename array, typename mdspan>
        void apply_rules( board<array, mdspan>& slice, const std::vector<live_count>& region_live_counts ) {

            std::ranges::for_each( region_live_counts, [&]( const auto& region_live_count ) {

                auto [ i, j, live_count ] = region_live_count;

                if ( slice.get_cell_state( i, j ) == 1 ) {

                    if ( 6 < live_count || live_count > 8 )
                        slice.set_cell_state( i, j, 0 );

                } else if ( live_count == 6 ) {
                    slice.set_cell_state( i, j, 1 );
                }
            });
        }

        template<typename array, typename mdspan, size_t cube_rank>
        void evolve( std::array<board<array, mdspan>, cube_rank + 2>& slices, const size_t slice ) {

            std::vector<live_count> region_live_counts;
            region_live_counts.reserve( slices[ slice ].get_board_height() * slices[ slice ].get_board_width() );

            get_region_live_counts<array, mdspan, cube_rank>( slices, slice, region_live_counts );

            toroidal_cube_evolve::apply_rules( slices[ slice ], region_live_counts );
        }

    }

}

#endif


#ifndef EVOLVE_BITSET_HPP
#define EVOLVE_BITSET_HPP

#include <bitset>
#include <vector>

namespace conway {

    template<template<typename, typename> class board, typename array, typename mdspan>
    void evolve_bitset( board<array, mdspan>& bd ) {

        std::bitset<mdspan::static_extent( 0 ) * mdspan::static_extent( 1 )> deactivated_cells;

        std::bitset<mdspan::static_extent( 0 ) * mdspan::static_extent( 1 )> activated_cells;

        std::vector<std::tuple<size_t, size_t, unsigned>> region_live_counts;
        region_live_counts.reserve( bd.cell_count() );

        get_region_live_counts_bitset( bd, region_live_counts, deactivated_cells );

        apply_rules_bitset( bd, region_live_counts, activated_cells );

        bd.add_activated_cells( activated_cells );

        bd.remove_deactivated_cells( deactivated_cells );
    }

    template<template<typename, typename> class board, typename array, typename mdspan>
    void get_region_live_counts_bitset( board<array, mdspan>& bd, std::vector<std::tuple<size_t, size_t, unsigned>>& region_live_counts,
                                        std::bitset<mdspan::static_extent( 0 ) * mdspan::static_extent( 1 )>& deactivated_cells ) {

        const auto active_cells = bd.get_active_cells();

        const size_t w = bd.get_board_width();

        for ( size_t k = 0; k < active_cells.size(); ++k ) {
            if ( active_cells[ k ] == 1 ) {
                unsigned region_live_count{};

                const size_t j = k % w;
                const size_t i = k / w;

                region_live_count = get_region_live_count( bd, i, j );

                if ( region_live_count == 0 ) {
                    // prepare cell for removal
                    deactivated_cells.set( k );
                }

                region_live_counts.emplace_back( std::tuple<size_t, size_t, unsigned>{ i, j, region_live_count } );
            }
        }
    }

    template<template<typename, typename> class board, typename array, typename mdspan>
    void add_neighbors_to_activated_bitset( board<array, mdspan>& bd, const size_t i, const size_t j,
                                            std::bitset<mdspan::static_extent( 0 ) * mdspan::static_extent( 1 )>& activated_cells ) {

        const size_t w = bd.get_board_width();

        for ( int di = -1; di <= 1; ++di ) {
            for ( int dj = -1; dj <= 1; ++dj ) {

                if ( di != 0 || dj != 0 ) {

                    const size_t j_ = static_cast<size_t>( static_cast<int>( j ) + dj );
                    const size_t i_ = static_cast<size_t>( static_cast<int>( i ) + di );

                    const size_t k = j_ + i_ * w;

                    activated_cells.set( k );
                }
            }
        }
    }

    template<template<typename, typename> class board, typename array, typename mdspan>
    void apply_rules_bitset( board<array, mdspan>& bd, const std::vector<std::tuple<size_t, size_t, unsigned>>& region_live_counts,
                            std::bitset<mdspan::static_extent( 0 ) * mdspan::static_extent( 1 )>& activated_cells ) {
        std::ranges::for_each( region_live_counts, [&]( const auto& region_live_count ) {

            // apply rules
            auto [ i, j, live_count ] = region_live_count;

            if ( live_count == 3 ) { // live cell survives, dead cell comes to life
                if ( bd.get_cell_state( i, j ) == 0 ) {
                    bd.set_cell_state( i, j, 1 );
                    add_neighbors_to_activated_bitset( bd, i, j, activated_cells );
                }
            } else if ( live_count != 4 ) // cell dies
                bd.set_cell_state( i, j, 0 );
        });
    }

}

#endif
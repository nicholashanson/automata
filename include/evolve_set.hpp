#ifndef EVOLVE_SET_HPP
#define EVOLVE_SET_HPP

#include <vector>

namespace conway {

    template<template<typename, typename> class board, typename array, typename mdspan>
    void evolve_set( board<array, mdspan>& bd ) {

        std::vector<std::tuple<size_t, size_t, unsigned>> region_live_counts;
        region_live_counts.reserve( bd.cell_count() );

        get_region_live_counts_set( bd, region_live_counts );
        apply_rules_set( bd, region_live_counts );
        remove_inactive_cells( bd, region_live_counts );
    }

    template<template<typename, typename> class board, typename array, typename mdspan>
    void get_region_live_counts_set( board<array, mdspan>& bd, std::vector<std::tuple<size_t, size_t, unsigned >>& region_live_counts ) {

        const auto active_cells = bd.get_active_cells();

        for ( const auto& [ i, j ] : active_cells ) {
            unsigned region_live_count{};

            region_live_count = get_region_live_count( bd, i, j );

            region_live_counts.emplace_back( std::tuple<size_t, size_t, unsigned>{ i, j, region_live_count } );
        }
    }

    template<template<typename, typename> class board, typename array, typename mdspan>
    void add_neighbors_to_active_cells( board<array, mdspan>& bd, const size_t i, const size_t j ) {

        for ( int di = -1; di <= 1; ++di )
            for ( int dj = -1; dj <= 1; ++dj )

                if ( di != 0 || dj != 0 )
                    bd.add_cell( i + di, j + dj );
    }

    template<template<typename, typename> class board, typename array, typename mdspan>
    void apply_rules_set( board<array, mdspan>& bd, const std::vector<std::tuple<size_t, size_t, unsigned>>& region_live_counts ) {
        std::ranges::for_each( region_live_counts, [&]( const auto& region_live_count ) {

            // apply rules
            auto [ i, j, live_count ] = region_live_count;

            if ( live_count == 3 ) { // live cell survives, dead cell comes to life
                if ( bd.get_cell_state( i, j ) == 0 ) {
                    bd.set_cell_state( i, j, 1 );
                    add_neighbors_to_active_cells( bd, i, j );
                }
            } else if ( live_count != 4 ) // cell dies
                bd.set_cell_state( i, j, 0 );
        });
    }

    template<template<typename, typename> class board, typename array, typename mdspan>
    void remove_inactive_cells( board<array, mdspan>& bd, const std::vector<std::tuple<size_t, size_t, unsigned>>& region_live_counts ) {

        const auto active_cells = bd.get_active_cells();

        std::ranges::for_each( region_live_counts, [&]( const auto& region_live_count ) {

            if ( std::get<2>( region_live_count) == 0 )
                bd.remove_cell( std::get<0>( region_live_count ), std::get<1>( region_live_count ) );
        });
    }

}

#endif


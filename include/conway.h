#ifndef CONWAY_H
#define CONWAY_H

// third-party includes
#include <mdspan-stable/include/mdspan/mdspan.hpp>

// standard library includes
#include <array>
#include <random>
#include <algorithm>

// local includes
#include <settings.h>

namespace conway {
    // dimensions for various boards
    using md5x5 = Kokkos::mdspan<bool, Kokkos::extents<size_t, 5, 5>>; // 5x5 board
    using md6x6 = Kokkos::mdspan<bool, Kokkos::extents<size_t, 6, 6>>; // 6x6 board
    using md7x7 = Kokkos::mdspan<bool, Kokkos::extents<size_t, 7, 7>>; // 7x7 board
    using md7x8 = Kokkos::mdspan<bool, Kokkos::extents<size_t, 7, 8>>; // 7x8 board

    // dimensions for various cell-state arrays
    using a25 = std::array<bool, 25>; // 5x5 board
    using a36 = std::array<bool, 36>; // 6x6 board
    using a49 = std::array<bool, 49>; // 7x7 board
    using a56 = std::array<bool, 56>; // 7x8 board

    // dimensions for board and under-lying cell-state storage
    using sim_mdspan = Kokkos::mdspan<bool, Kokkos::extents<size_t, settings::board_width + 2, settings::board_height + 2>>;
    using sim_array = std::array<bool, ( settings::board_width + 2 ) * ( settings::board_height + 2 ) >;

    // arrays for testing evolve
    extern a25 rule_one_0_before;
    extern a25 rule_one_0_after;
    extern a25 rule_one_1_before;
    extern a25 rule_one_1_after;
    extern a25 rule_two_2_before;
    extern a25 rule_two_2_after;
    extern a49 rule_two_3_before;
    extern a49 rule_two_3_after;

    // arrays for testing padding update
    extern a49 board_update_before;
    extern a49 board_update_after;

    // under-lying storage for cell states
    static sim_array cell_states;

    // still-life state
    extern a36 block;
    extern a56 beehive;

    template<typename array, typename mdspan>
    class board {
        public:
            board( array );
            bool operator==( const board& );
            const mdspan& get_current_state();

            size_t get_board_width() {
                return board_.static_extent( 1 );
            }

            size_t get_board_height() {
                return board_.static_extent( 0 );
            }

            bool get_cell_state( const size_t, const size_t );
            void set_cell_state( const size_t, const size_t, const bool );

            friend void evolve<array, mdspan>( board<array, mdspan>& );
        private:
            array cell_states_;
            mdspan board_;
    };

    template<typename array, typename mdspan>
    board<array, mdspan>::board( array cell_states ) :
        cell_states_( cell_states ), board_( cell_states.data() ) {
    }

    // test for equality between two boards
    template<typename array, typename mdspan>
    bool board<array, mdspan>::operator==( const board& rhs ) {
        for ( size_t i = 0; i < board_.static_extent( 0 ); i++ )
            for ( size_t j = 0; j < board_.static_extent( 1 ); j ++ )
                if ( board_[ i, j ] != rhs.board_[ i, j ] )
                    return false;
        return true;
    }

    template<typename array, typename mdspan>
    const mdspan& board<array, mdspan>::get_current_state() {
        return board_;
    }

    template<typename array, typename mdspan>
    bool board<array, mdspan>::get_cell_state( const size_t i, const size_t j ) {
        return board_[ i, j ];
    }

    template<typename array, typename mdspan>
    void board<array, mdspan>::set_cell_state( const size_t i, const size_t j, const bool state ) {
        board_[ i, j ] = state;
    }

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

    template<typename array, typename mdspan>
    void seed( board<array, mdspan>& bd ) {
        // generator for random state
        std::random_device rd;
        std::default_random_engine generator( rd() );
        std::uniform_int_distribution<int> distribution( 0, 1 );

        // assign random state to every cell in board
        // excluding padding
        for ( size_t i = 1; i < bd.get_board_height() - 1; i++ )
            for ( size_t j = 1; j < bd.get_board_width() - 1; j++ )
                bd.set_cell_state( i, j, distribution( generator ) );
    }

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

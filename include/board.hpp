#ifndef BOARD_HPP
#define BOARD_HPP

namespace conway {

    template<typename array, typename mdspan>
    class board {
        public:
            board( array );

            bool operator==( const board& );

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
        for ( size_t i = 0; i < board_.static_extent( 0 ); ++i )
            for ( size_t j = 0; j < board_.static_extent( 1 ); ++j )
                if ( board_[ i, j ] != rhs.board_[ i, j ] )
                    return false;
        return true;
    }

    template<typename array, typename mdspan>
    bool board<array, mdspan>::get_cell_state( const size_t i, const size_t j ) {
        return board_[ i, j ];
    }

    template<typename array, typename mdspan>
    void board<array, mdspan>::set_cell_state( const size_t i, const size_t j, const bool state ) {
        board_[ i, j ] = state;
    }

}

#endif

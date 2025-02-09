#ifndef BOARD_HPP
#define BOARD_HPP

#include <variant>

namespace conway {

    template<typename array, typename mdspan>
    class board {
        public:

            using value_type_ = typename mdspan::element_type;

            board();

            // constructor for owning board
            board( array );
            // constructor for non-owning board
            board( typename array::pointer );

            board& operator=( const board& other );

            board& operator=( board&& other ) noexcept;
#ifndef NDEBUG
            // equality operator only used for testing
            bool operator==( const board& ) const;
#endif

            size_t get_board_width() const {
                return board_.static_extent( 1 );
            }
            size_t get_board_height() const {
                return board_.static_extent( 0 );
            }

            decltype( auto ) get_cell_state( const size_t, const size_t ) const;

            void set_cell_state( const size_t, const size_t, const value_type_ );

            typename array::pointer get_data_handle();

#ifndef NDEBUG
            void print() {
                for ( size_t i = 0; i < get_board_height(); ++i ) {
                    for ( size_t j = 0; j < get_board_width(); ++j )
                        std::cout << board_[ i, j ] << ", ";
                    std::cout << std::endl;
                }
            }
#endif

        private:
            // array is either owning or non-owning
            std::variant<array, typename array::pointer> cell_states_;
            mdspan board_;
    };

    template<typename array, typename mdspan>
    board<array, mdspan>::board()
        : cell_states_( nullptr ), board_( nullptr ) {
    }

    // constructor for an owning board
    template<typename array, typename mdspan>
    board<array, mdspan>::board( array cell_states ) :
        cell_states_( std::move( cell_states ) ), board_( std::get<array>( cell_states_ ).data() ) {
    }

    // constructor for a non-owning board
    // cell_states = array.data()
    template<typename array, typename mdspan>
    board<array, mdspan>::board( typename array::pointer cell_states ) :
        cell_states_( cell_states ), board_( std::get<typename array::pointer>( cell_states_ ) ) {
    }

    template<typename array, typename mdspan>
    board<array, mdspan>& board<array, mdspan>::operator=( const board& other ) {
        if ( this != &other ) {

            /*
                valid copy-assignment:
                    ( 1 ) left.cell_states_ = nullptr, right.cell_states_ = non-nullptr
                    ( 2 ) left.cell_states_ = nullptr, right.cell_states_ = array

                invalid copy-assignment:
                    ( 1 ) left.cell_states_ = array, right.cell_states_ = any
                    ( 2 ) left.cell_states_ = non-nullptr, right.cell_states_ = any
            */            
            if ( auto ptr = std::get_if<typename array::pointer>( &cell_states_ ) ) {

                if (*ptr != nullptr) {
                   throw std::logic_error( "Cannot assign to a board that already contains valid state." );
                }
            }
            
            if ( auto ptr = std::get_if<typename array::pointer>( &cell_states_ ) ) {
                if (*ptr != nullptr) {
                    throw std::logic_error( "Cannot assign from a board that does not contain valid state." );
                }
            }

            if ( std::holds_alternative<array>( other.cell_states_ ) ) {
                cell_states_ = std::get<array>( other.cell_states_ );
            } else {
                cell_states_ = std::get<typename array::pointer>( other.cell_states_ );
            }

            if ( std::holds_alternative<array>( cell_states_ ) ) {
                board_ = mdspan( std::get<array>( cell_states_ ).data() );
            } else {
                board_ = mdspan( std::get<typename array::pointer>( cell_states_ ) );
            }
        }

        return *this;
    }

    template<typename array, typename mdspan>
    board<array, mdspan>& board<array, mdspan>::operator=( board&& other ) noexcept {
        if ( this != &other ) {

            cell_states_ = std::move( other.cell_states_ );

            if ( std::holds_alternative<array>( cell_states_ ) ) {
                board_ = mdspan( std::get<array>( cell_states_ ).data() );
            } else {
                board_ = mdspan( std::get<typename array::pointer>( cell_states_ ) );
            }
        }

        return *this;
    }

#ifndef NDEBUG
    // test for equality between two boards
    template<typename array, typename mdspan>
    bool board<array, mdspan>::operator==( const board& rhs ) const {
        for ( size_t i = 0; i < board_.static_extent( 0 ); ++i )
            for ( size_t j = 0; j < board_.static_extent( 1 ); ++j )
                if ( board_[ i, j ] != rhs.board_[ i, j ] )
                    return false;
        return true;
    }
#endif

    template<typename array, typename mdspan>
    decltype( auto ) board<array, mdspan>::get_cell_state( const size_t i, const size_t j ) const {
        return board_[ i, j ];
    }

    template<typename array, typename mdspan>
    void board<array, mdspan>::set_cell_state( const size_t i, const size_t j, const value_type_ state ) {
        board_[ i, j ] = state;
    }

    template<typename array, typename mdspan>
    typename array::pointer board<array, mdspan>::get_data_handle() {
        if ( std::holds_alternative<array>( cell_states_ ) )
            return std::get<array>( cell_states_ ).data();
        else
            return std::get<typename array::pointer>( cell_states_ );
    }

}

#endif

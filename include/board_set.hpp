#include <board.hpp>
#include <set>

namespace conway {

    template<typename array, typename mdspan>
    class board_set : public board<array, mdspan> {
        public:

            board_set()
                : board<array, mdspan>() {
                initialize();
            }

            board_set( array cell_states )
                : board<array, mdspan>( cell_states ) {
                initialize();
            }

            board_set& operator=( const board<array, mdspan>& other ) {

                board<array, mdspan>::operator=( other );

                return *this;
            }

            void initialize() {
                // this pointer is necessary to clarify scope
                for ( size_t i = 1; i < this->get_board_height() - 1; ++i ) {
                    for ( size_t j = 1; j < this->get_board_width() - 1; ++j ) {
                        cells_to_check_.insert( { i, j } );
                    }
                }
            }

            void add_cell ( const size_t i, const size_t j ) {
                if ( i >= 1 && i < this->get_board_height() - 1 && j >= 1 && j < this->get_board_width() - 1 )
                    cells_to_check_.insert( { i, j } );
            }

            void remove_cell( const size_t i, const size_t j ) {
                cells_to_check_.erase( { i, j } );
            }

            const auto& get_active_cells() {
                return cells_to_check_;
            }

            size_t cell_count() const {
                return cells_to_check_.size();
            }

        private:
            std::set<std::pair<size_t, size_t>> cells_to_check_;
    };

}

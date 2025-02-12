#ifndef CONWAY_BOARD_2D_HPP
#define CONWAY_BOARD_2D_HPP

#include <board.hpp>
#include <unordered_set>
#include <set>
#include <settings.hpp>

namespace conway {

    struct xor_hash {
        template<typename T1, typename T2>
        size_t operator()( const std::pair<T1, T2>& p ) const {
            return std::hash<T1>()( p.first ) ^ ( std::hash<T2>()( p.second ) << 1 );
        }
    };

    struct perfect_hash {
        size_t operator()( const std::pair<size_t, size_t>& p ) const {
            return p.first + p.second * settings::board_height;
        }
    };

    template<typename array, typename mdspan, typename set = std::set<std::pair<size_t, size_t>>>
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
                // this-pointer is necessary to clarify scope
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

            const auto& get_active_cells() const {
                return cells_to_check_;
            }

            size_t cell_count() const {
                return cells_to_check_.size();
            }

            void print_active_cells() const {
                for ( const auto& cell: cells_to_check_ )
                    std::cout << "( " << std::get<0>( cell ) << ", " << std::get<1>( cell ) << " ) ";
                std::cout << std::endl << "==================================" << std::endl;
            }

        private:
            set cells_to_check_;
    };

    template<typename array, typename mdspan>
    using board_unordered_set_xor = board_set<array, mdspan, std::unordered_set<std::pair<size_t, size_t>, xor_hash>>;

    template<typename array, typename mdspan>
    using board_unordered_set_perfect = board_set<array, mdspan, std::unordered_set<std::pair<size_t, size_t>, perfect_hash>>;
}

#endif


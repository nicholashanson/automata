#ifndef BOARD_SET_HPP
#define BOARD_SET_HPP

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

    /* 
        this is intended to be an optimized version of the grid that maintains a set of "acive" cells 
        so less cells need to be checked each evolution stage.

        it is intended to be an optimization but results may vary.

        the best result comes from using std::unordered_set with "perfect_hash", but using grids
        generated by the board_bitset class template gives better results.
    */
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

            /*
                copy assignment operator so we can write:

                    derived_class_instance = base_class_instance;

                this is used in testing so grids can have the same input.
            */
            board_set& operator=( const board<array, mdspan>& other ) {

                board<array, mdspan>::operator=( other );

                return *this;
            }

            // add every cell in the grid except padding cells to "cells_to_check_"
            void initialize() {
                // this-pointer is necessary to clarify scope
                for ( size_t i = 1; i < this->get_board_height() - 1; ++i ) {
                    for ( size_t j = 1; j < this->get_board_width() - 1; ++j ) {
                        cells_to_check_.insert( { i, j } );
                    }
                }
            }

            // add an inactive cell that becomes active to "cells_to_cehck_"
            void add_cell ( const size_t i, const size_t j ) {

                /*
                    when an inactive cell becomes active all its neighbors are added to "cells_to_check_"
                    
                    these neigbors might be padding cells so we use bounds-checking so padding cells don't get added
                    to "cells_to_check_
                */
                if ( i >= 1 && i < this->get_board_height() - 1 && j >= 1 && j < this->get_board_width() - 1 )
                    cells_to_check_.insert( { i, j } );
            }

            // when a cell becomes inactive it is removed from "cells_to_check_"
            void remove_cell( const size_t i, const size_t j ) {
                cells_to_check_.erase( { i, j } );
            }

            const auto& get_active_cells() const {
                return cells_to_check_;
            }

            // total number of currently "active" cells
            size_t cell_count() const {
                return cells_to_check_.size();
            }

#ifndef NDEBUG
            void print_active_cells() const {
                for ( const auto& cell: cells_to_check_ )
                    std::cout << "( " << std::get<0>( cell ) << ", " << std::get<1>( cell ) << " ) ";
                std::cout << std::endl << "==================================" << std::endl;
            }
#endif

        private:

            set cells_to_check_;                    // set of "active" cells
    };

    /*
        a couple of alias templates for convenience
    */
    template<typename array, typename mdspan>
    using board_unordered_set_xor = board_set<array, mdspan, std::unordered_set<std::pair<size_t, size_t>, xor_hash>>;

    template<typename array, typename mdspan>
    using board_unordered_set_perfect = board_set<array, mdspan, std::unordered_set<std::pair<size_t, size_t>, perfect_hash>>;
}

#endif


#ifndef CONWAY_BOARD_BITSET_HPP
#define CONWAY_BOARD_BITSET_HPP

#include <board.hpp>
#include <bitset>
#include <algorithm>

namespace conway {

    template<typename array, typename mdspan>
    class board_bitset : public board<array, mdspan> {
        public:

            board_bitset()
                : board<array, mdspan>::board() {
                initialize();
            }

            board_bitset( array cell_states )
                : board<array, mdspan>( cell_states ) {
                initialize();
            }

            board_bitset& operator=( const board<array, mdspan>& other ) {

                board<array, mdspan>::operator=( other );

                return *this;
            }

            void initialize() {               
                initialize_edge_mask();
                initialize_active_cells();
            }

            void initialize_edge_mask() {

                edge_mask_.set();

                const size_t height = mdspan::static_extent( 0 );
                const size_t width = mdspan::static_extent( 1 );

                for ( size_t j = 0; j < width; ++j ) {

                    edge_mask_.reset( j );
                    edge_mask_.reset( ( height - 1 ) * width + j );
                } 

                for ( size_t i = 0; i < height; ++ i ) {

                    edge_mask_.reset( i * width );
                    edge_mask_.reset( i * width + ( width - 1 ) );
                } 
            }

            void initialize_active_cells() {
                active_cells_.set();

                active_cells_ &= edge_mask_;
            }

            void add_activated_cells( std::bitset<mdspan::static_extent( 0 ) * mdspan::static_extent( 1 )>& activated_cells ) {
                active_cells_ |= activated_cells;
            } 

            void remove_deactivated_cells( std::bitset<mdspan::static_extent( 0 ) * mdspan::static_extent( 1 )>& deactivated_cells ) {

                active_cells_ ^= deactivated_cells;

                active_cells_ &= edge_mask_;
            }

            const auto& get_active_cells() const {
                return active_cells_;
            }

            size_t cell_count() const {
                return active_cells_.count();
            }

        private:
            std::bitset<mdspan::static_extent( 0 ) * mdspan::static_extent( 1 )> active_cells_;
            std::bitset<mdspan::static_extent( 0 ) * mdspan::static_extent( 1 )> edge_mask_;
    };
}

#endif


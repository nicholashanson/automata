#ifndef CUBE_HPP
#define CUBE_HPP

#include <global_aliases.hpp>

namespace conway {

    template<typename array, typename mdspan>
    class cube {

        using edge_mapping = std::tuple<size_t, size_t, bool>;
        using face_mapping = std::tuple<size_t, edge_mapping, edge_mapping, edge_mapping, edge_mapping>;

        public:
            cube( array blank_face ) : faces{ board<array, mdspan>( blank_face ),
                                              board<array, mdspan>( blank_face ),
                                              board<array, mdspan>( blank_face ),
                                              board<array, mdspan>( blank_face ),
                                              board<array, mdspan>( blank_face ),
                                              board<array, mdspan>( blank_face ) } {
            }

            cube( array face_0, array face_1, array face_2, array face_3, array face_4, array face_5 ) :
                faces{ board<array, mdspan>( face_0 ),
                       board<array, mdspan>( face_1 ),
                       board<array, mdspan>( face_2 ),
                       board<array, mdspan>( face_3 ),
                       board<array, mdspan>( face_4 ),
                       board<array, mdspan>( face_5 )
                 } {
            }

            void seed_faces() {
                for ( auto& face: faces )
                    seed( face );
            }
            void evolve_faces() {
                for ( auto& face: faces )
                    evolve( face );
            }

            template<size_t i>
            bool is_equal( const board<array, mdspan>& bd ) const {
                static_assert( i < 6, "Index i is out of bounds. It must be between 0 and 5." );

                return bd == faces[ i ];
            }

            bool get_cell_state( const size_t i, const size_t x, const size_t y ) const {
                return faces[ i ].get_cell_state( x, y );
            }

            void update_faces() {
                for ( const auto& face_mapping: face_mappings )
                    update_face( face_mapping );
            }

            void update_face( const face_mapping& );

        private:
            std::array<board<array, mdspan>, 6> faces;
            static const std::array<face_mapping, 6> face_mappings;
    };

    template<typename array, typename mdspan>
    const std::array<typename cube<array, mdspan>::face_mapping, 6> cube<array, mdspan>::face_mappings = {
        face_mapping{ 0,
            edge_mapping{ 3, 3, false },  // face 0 top row => face 3 bottom row, not reversed
            edge_mapping{ 4, 2, false },  // face 0 left column => face 4 right column, not reversed
            edge_mapping{ 5, 1, false },  // face 0 right column => face 5 left column, not reversed
            edge_mapping{ 1, 0, false }   // face 0 bottom row => face 1 top row, not reversed
        },
        face_mapping{ 1,
            edge_mapping{ 0, 3, false },  // face 1 top row => face 0 bottom row, not reversed
            edge_mapping{ 4, 3, true },   // face 1 left column => face 4 bottom row, reversed
            edge_mapping{ 5, 3, false},   // face 1 right column => face 5 bottom row, not reversed
            edge_mapping{ 2, 0, false }   // face 1 bottom row => face 2 top row, not reversed
        },
        face_mapping{ 2,
            edge_mapping{ 1, 3, false },  // face 2 top row => face 1 bottom row, not reversed
            edge_mapping{ 4, 1, true },   // face 2 left column => face 4 left column, reversed
            edge_mapping{ 5, 2, true },   // face 2 right column => face 5 right column, reversed
            edge_mapping{ 3, 0, false }   // face 2 bottom row => face 5 top row, not reversed
        },
        face_mapping{ 3,
            edge_mapping{ 2, 3, false },   // face 3 top row => face 2 bottom row, not reversed
            edge_mapping{ 4, 0, false },   // face 3 left column => face 4 top row, not reversed
            edge_mapping{ 5, 0, true },    // face 3 right column => face 5 top row, reversed
            edge_mapping{ 0, 0, false }    // face 3 bottom row => face 0 top row, not reversed
        },
        face_mapping{ 4,
            edge_mapping{ 3, 1, false },   // face 4 top row => face 3 left column, not reversed
            edge_mapping{ 2, 1, true },    // face 4 left column => face 2 left column, reversed
            edge_mapping{ 0, 1, false },   // face 4 right column => face 0 left column, not reversed
            edge_mapping{ 1, 1, true }     // face 4 bottom row => face 1 left row, reversed
        },
        face_mapping{ 5,
            edge_mapping{ 3, 2, true },   // face 5 top row => face 3 right column, reversed
            edge_mapping{ 0, 2, false },  // face 5 left column => face 0 right column, not reversed
            edge_mapping{ 2, 2, true },   // face 5 right column => face 2 right column, reversed
            edge_mapping{ 1, 2, false }   // face 5 bottom row => face 1 right column, not reversed
        }
    };

    template<typename array, typename mdspan>
    void cube<array, mdspan>::update_face( const face_mapping& fm ) {

        const auto& [ face_index, top_row_mapping, left_column_mapping, right_column_mapping, bottom_row_mapping ] = fm;

        const size_t bottom_index = faces[ face_index ].get_board_height() - 2;
        const size_t right_index = faces[ face_index ].get_board_width() - 2;
        const size_t bottom_padding = faces[ face_index ].get_board_height() - 1;
        const size_t right_padding = faces[ face_index ].get_board_width() - 1;

        const auto [ top_row_face, top_row_vector, top_reversed ] = top_row_mapping;
        const auto [ left_column_face, left_column_vector, left_reversed ] = left_column_mapping;
        const auto [ right_column_face, right_column_vector, right_reversed ] = right_column_mapping;
        const auto [ bottom_row_face, bottom_row_vector, bottom_reversed ] = bottom_row_mapping;

        for ( size_t column = 1; column < faces[ face_index ].get_board_width() - 1; ++column ) {

            // face 4 top row maps to face 3 left column, not reversed
            if ( top_row_vector == 1 )
                faces[ face_index ].set_cell_state( 0, column, faces[ top_row_face ].get_cell_state( column, 1 ) );

            // face 5 top row maps to face 3 right column, reversed
            if ( top_row_vector == 2 )
                faces[ face_index ].set_cell_state( 0, column, faces[ top_row_face ].get_cell_state( bottom_padding - column, right_index ) );

            // face 0 top row maps to face 3 bottom row, not reversed
            // face 1 top row maps to face 0 bottom row, not reversed
            if ( top_row_vector == 3 )
                faces[ face_index ].set_cell_state( 0, column, faces[ top_row_face ].get_cell_state( bottom_index, column ) );

            if ( bottom_row_vector == 0 )
                faces[ face_index ].set_cell_state( bottom_padding, column, faces[ bottom_row_face ].get_cell_state( 1, column ) );

            // face 4 bottom row maps to face 1 left column, reversed
            if ( bottom_row_vector == 1 )
                faces[ face_index ].set_cell_state( bottom_padding, column, faces[ bottom_row_face ].get_cell_state( bottom_padding - column, 1) );

            if ( bottom_row_vector == 2 )
                faces[ face_index ].set_cell_state( bottom_padding, column, faces[ bottom_row_face ].get_cell_state( column, right_index ) );
        }

        for ( size_t row = 1; row < faces[ face_index ].get_board_height() - 1; ++row ) {

            // face 3 left column maps to face 4 top row, not reversed
            if ( left_column_vector == 0 )
                faces[ face_index ].set_cell_state( row, 0, faces[ left_column_face ].get_cell_state( 1, row ) );

            if ( left_column_vector == 1 )
                faces[ face_index ].set_cell_state( row, 0, faces[ left_column_face ].get_cell_state( bottom_padding - row,  1 ) );

            if ( left_column_vector == 2 )
                faces[ face_index ].set_cell_state( row, 0, faces[ left_column_face ].get_cell_state( row, right_index ) );

            if ( left_column_vector == 3 )
                faces[ face_index ].set_cell_state( row, 0, faces[ left_column_face ].get_cell_state( bottom_index, right_padding - row ) );

            if ( right_column_vector == 0 )
                faces[ face_index ].set_cell_state( row, right_padding, faces[ right_column_face ].get_cell_state( 1, right_padding - row ) );

            if ( right_column_vector == 1 )
                faces[ face_index ].set_cell_state( row, right_padding, faces[ right_column_face ].get_cell_state( row, 1 ) );

            if ( right_column_vector == 2 )
                faces[ face_index ].set_cell_state( row, right_padding, faces[ right_column_face ].get_cell_state( bottom_padding - row, right_index ) );

            if ( right_column_vector == 3 )
                faces[ face_index ].set_cell_state( row, right_padding, faces[ right_column_face ].get_cell_state( bottom_index, row ) );
        }
    }

}

#endif

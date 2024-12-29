namespace conway {

    template<typename array, typename mdspan, template<typename, typename> class board, size_t cube_rank>
    class toroidal_cube {
        public:

            toroidal_cube( array array_0 ) {

                for ( size_t i = 1; i < cube_rank + 1; ++i )
                    slices[ i ] = board<array, mdspan>( array_0 );

                slices[ 0 ] = board<array, mdspan>( slices[ cube_rank ].get_data_handle() );
                slices[ cube_rank + 1 ] = board<array, mdspan>( slices[ 1 ].get_data_handle() );

            }

            toroidal_cube( array array_0, array array_1, array array_2, array array_3, array array_4 ) {

                slices[ 1 ] = board<array, mdspan>( array_0 );
                slices[ 2 ] = board<array, mdspan>( array_1 );
                slices[ 3 ] = board<array, mdspan>( array_2 );
                slices[ 4 ] = board<array, mdspan>( array_3 );
                slices[ 5 ] = board<array, mdspan>( array_4 );

                slices[ 0 ] = board<array, mdspan>( slices[ cube_rank ].get_data_handle() );
                slices[ cube_rank + 1 ] = board<array, mdspan>( slices[ 1 ].get_data_handle() );

            }

#ifndef NDEBUG
            template<size_t i>
            bool equal_boards( const size_t slice, const board<array, mdspan>& other_board ) {

                if constexpr ( i == 0 )
                    return slices[ slice ] == other_board;

                else if constexpr ( i == 1 ) {
                    for ( size_t j = 0; j < cube_rank + 2; ++j )
                        for ( size_t k = 0; k < cube_rank + 2; ++k )
                            if ( slices[ j ].get_cell_state( slice, k ) != other_board.get_cell_state( j, k ) )
                                return false;
                    return true;
                }

                else if constexpr ( i == 2 ) {
                    for ( size_t j = 0; j < cube_rank + 2; ++j )
                        for ( size_t k = 0; k < cube_rank + 2; ++k )
                            if ( slices[ j ].get_cell_state( k, slice ) != other_board.get_cell_state( k, j ) )
                                return false;
                    return true;
                }

            }
#endif

            void seed_cube() {
                for ( size_t i = 1; i < cube_rank + 1; ++i )
                    seed( slices[ i ] );
            }

            void evolve_cube() {
                for ( size_t i = 1; i < cube_rank + 1; ++i )
                    toroidal_cube_evolve::evolve<array, mdspan, cube_rank>( slices, i );
            }

            void update_cube_padding() {
                for ( size_t i = 1; i < cube_rank + 1; ++ i )
                    update_padding( slices[ i ] );
            }

            decltype( auto ) get_cell_state( const size_t slice, const size_t i, const size_t j ) const {
                return slices[ slice ].get_cell_state( i, j );
            }


#ifndef NDEBUG
            void print_cube() {
                for ( auto& slice : slices ) {
                    slice.print();
                    std::cout << "===============================================" << std::endl;
                }
            }
#endif

        private:
            std::array<board<array, mdspan>, cube_rank + 2> slices;
    };

}

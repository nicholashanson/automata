namespace conway {

    template<typename array, typename mdspan, template<typename, typename> class board, size_t cube_rank>
    void draw_toroidal_cube_slice( const conway::toroidal_cube<array, mdspan, board, cube_rank>& cube,
								   const size_t slice,
                                   const Model& blue_cube,
                                   const Model& white_cube ) {

        constexpr float z_offset_base = settings::cube_cell_size * cube_rank;

        float z_offset = z_offset_base - settings::cube_cell_size * slice;

        for ( size_t x = 1; x < cube_rank + 1; ++x )
            for ( size_t y = 1; y < cube_rank + 1; ++y ) {

                float x_pos = ( x - cube_rank / 2.0f ) * settings::cube_cell_size + settings::cube_cell_size / 2.0f;
                float y_pos = ( cube_rank / 2.0f - y ) * settings::cube_cell_size - settings::cube_cell_size / 2.0f;

                Vector3 cell_position = Vector3{ x_pos, y_pos, z_offset };

                DrawCubeWires( cell_position, settings::cube_cell_size, settings::cube_cell_size, settings::cube_cell_size, DARKGRAY);

                if ( cube.get_cell_state( slice, y + 1, x + 1) == 1 )
                    DrawModelEx( white_cube, cell_position, Vector3{ 1, 0, 0 }, 0.0f, Vector3{ 1, 1, 1 }, WHITE );
            }
    }

    template<typename array, typename mdspan, template<typename, typename> class board, size_t cube_rank>
    void draw_toroidal_cube( const conway::toroidal_cube<array, mdspan, board, cube_rank>& cube,
                             const Model& blue_cube,
                             const Model& white_cube) {

        // loop through each slice and draw it stacked along the z-axis
        for ( size_t i = 1; i < cube_rank; ++i )
            draw_toroidal_cube_slice( cube, i, blue_cube, white_cube );
    }

}


#include "raymath.h"
#include "raylib.h"

// local includes
#include <settings.hpp>

namespace conway {

    // render cylinder
    template<typename array, typename mdspan>
    void draw_cylinder( const board<array, mdspan>& bd, Model& blue_cube, Model& white_cube ) {

        constexpr float radius = ( ( conway::settings::board_width ) * settings::cube_cell_size ) / ( 2 * PI );

        constexpr float angle_step = 360.0f / ( settings::board_width );

        // loop through each cell in the board
        for ( size_t y = 0; y < settings::board_height; ++y ) {

            // the height of this row cells along the central axis of the cylinder
            const float y_offset = ( y - settings::board_height / 2.0f ) * settings::cube_cell_size + settings::cube_cell_size / 2.0f;

            for ( size_t x = 0; x < settings::board_width; ++x ) {

                // the cells position in the xy plane
                Vector3 cell_position = Vector3{ radius, y_offset, 0 };

                // rotate the cell to its final position
                Matrix rotation_matrix = MatrixRotate( Vector3{ 0, 1, 0 }, x * angle_step * DEG2RAD );
                cell_position = Vector3Transform( cell_position, rotation_matrix );

                // add a border effect to the cell
                DrawCubeWires( cell_position, 0.25f, 0.25f, 0.25f, DARKGRAY );

                // finally render the cell
                if ( bd.get_cell_state( x + 1, y + 1 ) == 1 )
                    // blue = live
                    DrawModelEx( blue_cube, cell_position, Vector3{ 1, 0, 0 }, 0.0f, Vector3{ 1, 1, 1 }, BLUE );
                else
                    // white = dead
                    DrawModelEx( white_cube, cell_position, Vector3{ 1, 0, 0 }, 0.0f, Vector3{ 1, 1, 1 }, WHITE );
            }
        }
    }

}

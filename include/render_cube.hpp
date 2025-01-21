#include "raylib.h"
#include "raymath.h"

// local includes
#include <settings.hpp>

namespace conway {

    static const std::array<Vector3, 6> cube_face_rotation_axes = {
        Vector3{ 1, 0, 0 }, // face 0 is not rotated
        Vector3{ 1, 0, 0 }, // face 1 is rotated 90 degrees around the x-axis
        Vector3{ 1, 0, 0 }, // face 2 is rotated 180 degrees around the x-axis
        Vector3{ 1, 0, 0 }, // face 3 is rotated -90 degrees around the x-axis
        Vector3{ 0, 1, 0 }, // face 4 is rotated -90 degrees around the y-axis
        Vector3{ 0, 1, 0 }  // face 5 is rotated 90 degrees around the y-axis
    };

    static const std::array<float, 6> cube_face_rotation_angles = {
        0.0f,    // face 0 is not rotated
        90.0f,   // face 1 is rotated 90 degrees around the x-axis
        180.0f,  // face 2 is rotated 180 degrees around the x-axis
        -90.0f,  // face 3 is rotated -90 degrees around the x-axis
        -90.0f,  // face 4 is rotated -90 degrees around the y-axis
        90.0f    // face 5 is rotated 90 degrees around the y-axis
    };

    // render a single face of the cube
    template<typename array, typename mdspan>
    void draw_cube_face( const conway::cube<array, mdspan>& cube, const size_t face,
        const Model& blue_cube, const Model& white_cube,
        const Vector3 rotation_axis, const float rotation_angle ) {

        /*
            rendering cube faces:
            ( 1 ) arrange the cubes that make up the face in the x-y plane
            ( 2 ) move the face to a position on the z-axis
            ( 3 ) rotate the face around either the x-axis or y-axis to form a cube
        */

        // z offset is the same for every face
        constexpr float z_offset = settings::cube_cell_size * ( settings::board_height / 2.0f ) + settings::cube_cell_size / 2.0f;

        // loop through every cell in the face
        for ( size_t x = 0; x < settings::board_height; ++x ) {
            for ( size_t y = 0; y < settings::board_height; ++y ) {

                // position cell in the xy plane
                float x_pos = ( x - settings::board_height / 2.0f ) * settings::cube_cell_size + settings::cube_cell_size / 2.0f;
                float y_pos = ( settings::board_height / 2.0f - y ) * settings::cube_cell_size - settings::cube_cell_size / 2.0f;

                Vector3 cell_position = Vector3{ x_pos, y_pos, z_offset };

                // rotate cell in space to orientate the cube face
                Matrix rotation_matrix = MatrixRotate( rotation_axis, rotation_angle * DEG2RAD );
                cell_position = Vector3Transform( cell_position, rotation_matrix );

                // create a border effect around the cube
                DrawCubeWires( cell_position, settings::cube_cell_size, settings::cube_cell_size, settings::cube_cell_size, DARKGRAY );

                // render cube
                if ( cube.get_cell_state( face, y + 1, x + 1 ) == 1 )
                    // blue = live
                    DrawModelEx( blue_cube, cell_position, Vector3{ 1, 0, 0 }, 0.0f, Vector3{ 1, 1, 1 }, BLUE );
                else
                    // white = dead
                    DrawModelEx( white_cube, cell_position, Vector3{ 1, 0, 0 }, 0.0f, Vector3{ 1, 1, 1 }, WHITE );
            }
        }
    }

    // render each face of the cube
    template<typename array, typename mdspan>
    void draw_cube( const conway::cube<array, mdspan>& cube, const Model& blue_cube,const Model& white_cube ) {
        for ( size_t i = 0; i < 6; ++i )
            draw_cube_face( cube, i, blue_cube, white_cube, cube_face_rotation_axes[ i ], cube_face_rotation_angles[ i ] );
    }

}

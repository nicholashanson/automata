#include <settings.hpp>
#include "raylib.h"
#include "rlgl.h"
#include "raymath.h"
#include <camera.hpp>

namespace conway {

    static const std::array<Vector3, 6> cube_face_rotation_axes = {
        Vector3{ 1, 0, 0 }, // face 0
        Vector3{ 1, 0, 0 }, // face 1
        Vector3{ 1, 0, 0 }, // face 2
        Vector3{ 1, 0, 0 }, // face 3
        Vector3{ 0, 1, 0 }, // face 4
        Vector3{ 0, 1, 0 }  // face 5
    };

    static const std::array<float, 6> cube_face_rotation_angles = {
        0.0f,    // face 0
        90.0f,   // face 1
        180.0f,  // face 2
        -90.0f,  // face 3
        -90.0f,  // face 4
        90.0f    // face 5
    };

    template<typename array, typename mdspan>
    void draw_cube_face( const conway::cube<array, mdspan>& cube, const size_t face,
        const Model& blue_cube, const Model& white_cube,
        const Vector3 rotation_axis, const float rotation_angle ) {

        const float z_offset = settings::cube_cell_size * ( settings::board_height / 2.0f ) + settings::cube_cell_size / 2.0f;

        for ( size_t x = 0; x < settings::board_height; ++x ) {
            for ( size_t y = 0; y < settings::board_height; ++y ) {

                float x_pos = ( x - settings::board_height / 2.0f ) * settings::cube_cell_size + settings::cube_cell_size / 2.0f;
                float y_pos = ( settings::board_height / 2.0f - y ) * settings::cube_cell_size - settings::cube_cell_size / 2.0f;

                Vector3 cell_position = Vector3{ x_pos, y_pos, z_offset };

                Matrix rotation_matrix = MatrixRotate( rotation_axis, rotation_angle * DEG2RAD );
                cell_position = Vector3Transform( cell_position, rotation_matrix );

                DrawCubeWires( cell_position, settings::cube_cell_size, settings::cube_cell_size, settings::cube_cell_size, DARKGRAY );

                if ( cube.get_cell_state( face, y + 1, x + 1 ) == 1 )
                    DrawModelEx( blue_cube, cell_position, Vector3{ 1, 0, 0 }, 0.0f, Vector3{ 1, 1, 1 }, BLUE );
                else
                    DrawModelEx( white_cube, cell_position, Vector3{ 1, 0, 0 }, 0.0f, Vector3{ 1, 1, 1 }, WHITE );
            }
        }
    }

    template<typename array, typename mdspan>
    void draw_cube( const conway::cube<array, mdspan>& cube, const Model& blue_cube,const Model& white_cube ) {
        for ( size_t i = 0; i < 6; ++i )
            draw_cube_face( cube, i, blue_cube, white_cube, cube_face_rotation_axes[ i ], cube_face_rotation_angles[ i ] );
    }

    template<typename array, typename mdspan>
    void draw_cylinder( const board<array, mdspan>& bd, Model& blue_cube, Model& white_cube ) {

        const float radius = ( ( conway::settings::board_width ) * settings::cube_cell_size ) / ( 2 * PI );

        const float angle_step = 360.0f / ( settings::board_width );

        for ( size_t y = 0; y < settings::board_height; ++y ) {

            const float y_offset = ( y - settings::board_height / 2.0f ) * settings::cube_cell_size + settings::cube_cell_size / 2.0f;

            for ( size_t x = 0; x < settings::board_width; ++x ) {

                Vector3 cell_position = Vector3{ radius, y_offset, 0 };

                Matrix rotation_matrix = MatrixRotate( Vector3{ 0, 1, 0 }, x * angle_step * DEG2RAD );
                Vector3Transform( cell_position, rotation_matrix );

                DrawCubeWires( cell_position, 0.25f, 0.25f, 0.25f, DARKGRAY );

                if ( bd.get_cell_state( x + 1, y + 1 ) == 1 )
                    DrawModelEx( blue_cube, cell_position, Vector3{ 1, 0, 0 }, 0.0f, Vector3{ 1, 1, 1 }, BLUE );
                else
                    DrawModelEx( white_cube, cell_position, Vector3{ 1, 0, 0 }, 0.0f, Vector3{ 1, 1, 1 }, WHITE );
            }
        }
    }

    void draw_cell( size_t i, size_t j ) {
        DrawRectangle( i * settings::square_size,
                       j * settings::square_size,
                       settings::square_size - 1,
                       settings::square_size - 1, BLUE );
    }

    void draw_background() {
        ClearBackground( BLACK );
        for ( size_t i = 0; i < settings::board_width; ++i )
            for ( size_t j = 0; j < settings::board_height; ++j )
                DrawRectangle( i * settings::square_size,
                               j * settings::square_size,
                               settings::square_size - 1,
                               settings::square_size - 1, WHITE );
    }

}



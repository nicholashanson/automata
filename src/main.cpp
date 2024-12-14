#include "raylib.h"
#include "raymath.h"
#include "conway.hpp"
#include "rlgl.h"
#include <iostream>

constexpr float cube_size = 1.5f;

template<typename array, typename mdspan>
void draw_cube_face( Vector3 face_center, float r,
                     conway::board<array, mdspan>& bd ) {
    rlPushMatrix();
    rlRotatef( r, 1, 0, 0 );
    DrawCube( face_center,
              conway::settings::square_size * 1.9f,
              conway::settings::square_size * 1.9f,
              conway::settings::square_size * 1.9f,
              BLUE );
    rlPopMatrix();
}

void draw_cell( size_t i, size_t j ) {
    DrawRectangle( i * conway::settings::square_size,
                   j * conway::settings::square_size,
                   conway::settings::square_size - 1,
                   conway::settings::square_size - 1, BLUE );
}

void draw_background()
{
    ClearBackground( BLACK );
    for ( size_t i = 0; i < conway::settings::board_width; ++i )
        for ( size_t j = 0; j < conway::settings::board_height; ++j )
            DrawRectangle( i * conway::settings::square_size,
                           j * conway::settings::square_size,
                           conway::settings::square_size - 1,
                           conway::settings::square_size - 1, WHITE );
}

int main( int argc, char* argv[] )
{

    /*
    conway::board<conway::sim_array, conway::sim_mdspan> board( conway::cell_states );

    conway::seed( board );
    */

    const int screen_width = 800;
    const int screen_height = 600;

    //InitWindow( screen_width, screen_height, "Game of Life" );

    /*
    InitWindow( conway::settings::window_width, conway::settings::window_height,
                "Game of Life" );
    */

    //SetTargetFPS( 1 );

    Camera camera = { 0 };
    camera.position = ( Vector3 ){ 20.0f, 20.0f, 20.0f };
    camera.target = ( Vector3 ){ 0.0f, 0.0f, 0.0f };
    camera.up = ( Vector3 ){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    CameraMode( camera, CAMERA_PERSPECTIVE );

    conway::cube<conway::sim_array, conway::sim_mdspan> cube;

    Model _cube = LoadModelFromMesh( GenMeshCube( 2.0f, 2.0f, 2.0f ) );

    //while ( !WindowShouldClose() ) {

        //BeginDrawing();

        //ClearBackground( RAYWHITE );
        //BeginMode3D( camera );

        //DrawModel( _cube, ( Vector3 ) { 0.0, 1.0f, 0.0 }, 1.0f, BLACK );

        //DrawGrid(10, 1.0f);

        const float square_size = 2.5f;
        const float square_thickness = 0.1f;
        const float dx = 0.5f;
        const float dy = 0.25f;
        const Vector3 square_dimensions = (Vector3){ square_size, square_size, square_thickness };

        //DrawModelEx( _cube, ( Vector3 ) { 0, 2, 2 }, ( Vector3 ) { 1, 0, 0 }, 0, (Vector3){ square_size, square_size, square_thickness }, BLUE );
        float x_offset = ( conway::settings::board_width / 2 )*square_size;
        x_offset = -x_offset;
        x_offset = x_offset + square_size;
        const float y_offset = ( conway::settings::board_height / 2 )*square_size - square_size;
        const float z_pos = ( conway::settings::board_height / 2 ) * square_size;

        for ( size_t x = 1; x < conway::settings::board_width - 1; ++ x )
            for ( size_t y = 1; y < conway::settings::board_height - 1; ++y ) {
                std::cout << "x_offset: " << x_offset << std::endl;
                std::cout << "y_offset: " << y_offset << std::endl;
                float x_pos = x_offset + x*square_size;
                float y_pos = y_offset - y*square_size;
                std::cout << "x: " << x << ", xpos: " << x_pos << std::endl;
                std::cout << "ypos: " << y_pos << std::endl;
                //if ( x == y )
                    //DrawModelEx( _cube, ( Vector3 ) { x_pos, y_pos, z_pos }, ( Vector3 ) { 1, 0, 0 }, 0, square_dimensions, RED );
                //else
                    //DrawModelEx( _cube, ( Vector3 ) { x_pos, y_pos, z_pos }, ( Vector3 ) { 1, 0, 0 }, 0, square_dimensions, BLUE );
        }
        //DrawModelEx( _cube, ( Vector3 ) { 0 - dx, 0 - dx, 1 }, ( Vector3 ) { 1, 0, 0 }, 0, square_dimensions, RED );
        //DrawModelEx( _cube, ( Vector3 ) { 0 + dx, 0 + dx, 1 }, ( Vector3 ) { 1, 0, 0 }, 0, square_dimensions, RED );
        //DrawModelEx( _cube, ( Vector3 ) { 0 - dx, 0 + dx, 1 }, ( Vector3 ) { 1, 0, 0 }, 0, square_dimensions, BLUE );

        //DrawModelEx( _cube, ( Vector3 ) { 0 + dx, 0 + dx, -1 }, ( Vector3 ) { 1, 0, 0 }, 0, (Vector3){ square_size, square_size, square_thickness }, BLUE );
        //DrawModelEx( _cube, ( Vector3 ) { 0 + dx, 0 - dx, -1 }, ( Vector3 ) { 1, 0, 0 }, 0, (Vector3){ square_size, square_size, square_thickness }, BLUE );
        //DrawModelEx( _cube, ( Vector3 ) { 0 - dx, 0 + dx, -1 }, ( Vector3 ) { 1, 0, 0 }, 0, (Vector3){ square_size, square_size, square_thickness }, BLUE );
        //DrawModelEx( _cube, ( Vector3 ) { 0 - dx, 0 - dx, -1 }, ( Vector3 ) { 1, 0, 0 }, 0, (Vector3){ square_size, square_size, square_thickness }, BLUE );
        //DrawModelEx( _cube, ( Vector3 ) { 0, 0, 0 }, ( Vector3 ) { 1, 0, 0 }, 90, (Vector3){ square_size, square_size, square_thickness }, GREEN );
        //DrawModelEx( _cube, ( Vector3 ) { 0, 4, 0 }, ( Vector3 ) { 1, 0, 0 }, 90, (Vector3){ square_size, square_size, square_thickness }, GREEN );
        //DrawModelEx( _cube, ( Vector3 ) { -2, 2, 0 }, ( Vector3 ) { 0, 1, 0 }, 90, (Vector3){ square_size, square_size, square_thickness }, RED );
        //DrawModelEx( _cube, ( Vector3 ) { 2, 2, 0 }, ( Vector3 ) { 0, 1, 0 }, 90, (Vector3){ square_size, square_size, square_thickness }, RED );

        auto& faces = cube.faces;
        //draw_cube_face( { 0.0f, cube_size / 2, 0.0f }, 1.0f, faces[0] ); // Front
        //draw_cube_face( { 0.0f, cube_size * 9, 0.0f }, 0, faces[1] );  // Back
        //draw_cube_face( { -cube_size / 2, 0.0f, 0.0f }, { -1.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, faces[2] ); // Left
        //draw_cube_face( { cube_size / 2, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, faces[3] );  // Right
        //draw_cube_face( { 0.0f, cube_size / 2, 0.0f }, { 0.0f, 1.0f, 0.0f }, { 0.0f, 0.0f, -1.0f }, faces[4] ); // Top
        //draw_cube_face( { 0.0f, -cube_size / 2, 0.0f }, { 0.0f, -1.0f, 0.0f }, { 0.0f, 0.0f, 1.0f }, faces[5] ); // Bottom

        /*
        for ( size_t i = 1; i < board.get_board_height() - 1; ++i )
            for ( size_t j = 1; j < board.get_board_width() - 1; ++j )
                if ( board.get_cell_state( i, j ) == 1 )
                    draw_cell( i - 1, j - 1);
        */

        //EndDrawing();

        //EndMode3D();

        //cube.evolve_face();

        //conway::update_padding( board );
        //conway::evolve( board );

    //}

    //CloseWindow();

}


#include "raylib.h"
#include "raymath.h"
#include "conway.hpp"
#include "rlgl.h"
#include <iostream>
#include <rendering.hpp>
#include <cstring>
#include <controls.hpp>

int main(int argc, char* argv[]) {

    const int screen_width = 800;
    const int screen_height = 600;

    // reduces Moiré pattern with higher-dimensional boards
    SetConfigFlags( FLAG_MSAA_4X_HINT );

    InitWindow( screen_width, screen_height, "Game of Life" );

    SetTargetFPS( 10 );

    conway::set_up_camera();

    // instance of cube initiated with zeroes
    conway::cube<conway::sim_array, conway::sim_mdspan> cube( conway::cell_states );

    // instance of toroidal cube initiated with zeroes
    conway::toroidal_cube<conway::sim_array, conway::sim_mdspan, conway::board, conway::settings::cube_rank> t_cube( conway::cell_states );

    // instance of board initiated with zeroes
    conway::board_bitset<conway::sim_array, conway::sim_mdspan> board( conway::cell_states );

    // set-up cube
    if ( strcmp( argv[ 1 ], "cube" ) == 0 ) {
        cube.seed_faces();
        cube.update_faces();
    }

    // set-up toroidal cube
    if ( strcmp( argv[ 1 ], "toroidal" ) == 0 ) {
        t_cube.seed_cube();
        t_cube.update_cube_padding();
    }

    // set-up board
    if ( strcmp( argv[ 1 ], "cylinder" ) == 0 || strcmp( argv[ 1 ], "board" ) == 0 ) {
        conway::seed( board );
        conway::update_padding( board );
    }

    // blue cube = live cell
    // white cube = dead cell
    Model blue_cube = LoadModelFromMesh( GenMeshCube( 0.25f, 0.25f, 0.25f ) );
    Model white_cube = LoadModelFromMesh( GenMeshCube( 0.25f, 0.25f, 0.25f ) );

    while ( !WindowShouldClose() ) {

        BeginDrawing();

        ClearBackground( BLACK );

        BeginMode3D( conway::camera );

        if ( strcmp( argv[ 1 ], "cylinder" ) == 0 )
            conway::draw_cylinder( board, blue_cube, white_cube );

        if ( strcmp( argv[ 1 ], "toroidal" ) == 0 )
            conway::draw_toroidal_cube( t_cube, blue_cube, white_cube );

        if ( strcmp( argv[ 1 ], "cube" ) == 0 )
            conway::draw_cube( cube, blue_cube, white_cube );

        EndMode3D();

        EndDrawing();

        // update cube faces
        if ( strcmp( argv[ 1 ], "cube" ) == 0 ) {
            
            cube.evolve_faces();
            cube.update_faces();
        }

        if ( strcmp( argv[ 1 ], "toroidal" ) == 0 ) {

            t_cube.evolve_cube();
            t_cube.update_cube_padding();
        }

        // update board
        if ( strcmp( argv[ 1 ], "cylinder" ) == 0 || strcmp( argv[ 1 ], "board" ) == 0 ) {

            conway::evolve_bitset( board );
            conway::update_padding( board );
        }

        // get user input
        conway::handle_controls();

    }

    CloseWindow();

    return 0;
}

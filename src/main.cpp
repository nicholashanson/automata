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

    SetConfigFlags( FLAG_MSAA_4X_HINT );

    InitWindow( screen_width, screen_height, "Game of Life" );

    SetTargetFPS( 10 );

    conway::set_up_camera();

    conway::cube<conway::sim_array, conway::sim_mdspan> cube( conway::cell_states );
    conway::board<conway::sim_array, conway::sim_mdspan> board( conway::cell_states );

    if ( strcmp( argv[ 1 ], "cube" ) == 0 ) {
        cube.seed_faces();
        cube.update_faces();
    }

    if ( strcmp( argv[ 1 ], "cylinder" ) == 0 || strcmp( argv[ 1 ], "board" ) == 0 ) {
        conway::seed( board );
        conway::update_padding( board );
    }

    Model blue_cube = LoadModelFromMesh( GenMeshCube( 0.25f, 0.25f, 0.25f ) );
    Model white_cube = LoadModelFromMesh( GenMeshCube( 0.25f, 0.25f, 0.25f ) );

    while ( !WindowShouldClose() ) {

        BeginDrawing();

        ClearBackground( BLACK );

        BeginMode3D( conway::camera );

        if ( strcmp( argv[ 1 ], "cylinder" ) == 0 )
            conway::draw_cylinder( board, blue_cube, white_cube );

        if ( strcmp( argv[ 1 ], "cube" ) == 0 )
            conway::draw_cube( cube, blue_cube, white_cube );

        EndMode3D();

        EndDrawing();

        if ( strcmp( argv[ 1 ], "cube" ) == 0 ) {
            cube.evolve_faces();
            cube.update_faces();
        }

        if ( strcmp( argv[ 1 ], "cylinder" ) == 0 || strcmp( argv[ 1 ], "board" ) == 0 ) {
            conway::evolve( board );
            conway::update_padding( board );
        }

        conway::handle_controls();

    }

    CloseWindow();

    return 0;
}

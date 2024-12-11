#include "raylib.h"
#include "conway.h"

void draw_cell( size_t i, size_t j )
{
    DrawRectangle( i * conway::settings::square_size,
                   j * conway::settings::square_size,
                   conway::settings::square_size - 1,
                   conway::settings::square_size - 1, BLUE );
}

void draw_background()
{
    ClearBackground( BLACK );
    for ( size_t i = 0; i < conway::settings::board_width; i++ )
        for ( size_t j = 0; j < conway::settings::board_height; j++ )
            DrawRectangle( i * conway::settings::square_size,
                           j * conway::settings::square_size,
                           conway::settings::square_size - 1,
                           conway::settings::square_size - 1, WHITE );
}

int main()
{
    conway::board<conway::sim_array, conway::sim_mdspan> board( conway::cell_states );

    conway::seed( board );

    InitWindow( conway::settings::window_width, conway::settings::window_height,
                "Game of Life" );

    SetTargetFPS( 10 );

    while ( !WindowShouldClose() ) {

        BeginDrawing();

        draw_background();

        for ( size_t i = 1; i < board.get_board_height(); i++ )
            for ( size_t j = 1; j < board.get_board_width(); j++ )
                if ( board.get_cell_state( i, j ) == 1 )
                    draw_cell( i - 1, j - 1);

        EndDrawing();

        conway::update_padding( board );
        conway::evolve( board );

    }

    CloseWindow();

}


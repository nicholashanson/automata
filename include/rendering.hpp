#include "raylib.h"
#include "raymath.h"

// local includes
#include <settings.hpp>
#include <render_cube.hpp>
#include <render_cylinder.hpp>
#include <render_toroidal_cube.hpp>

namespace conway {

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



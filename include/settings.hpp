#ifndef SETTINGS_H
#define SETTINGS_H

namespace conway {

    namespace settings {

        constexpr size_t board_width = 100;
        constexpr size_t board_height = 100;

        constexpr size_t cube_rank = board_height;

        constexpr float camera_x = 30.0f;
        constexpr float camera_y = 30.0f;
        constexpr float camera_z = 30.0f;

        constexpr size_t square_size = 5;

        constexpr float cube_cell_size = 0.25f;

        constexpr size_t window_width = board_width * square_size;
        constexpr size_t window_height = board_height * square_size;

        // torus
        constexpr float major_radius = 5.0f;
        constexpr float minor_radius = 2.0f;

    }

}

#endif

#ifndef SETTINGS_H
#define SETTINGS_H

namespace conway {

    namespace settings {

        const size_t board_width = 40;
        const size_t board_height = 40;

        const float camera_x = 30.0f;
        const float camera_y = 30.0f;
        const float camera_z = 30.0f;
        ;
        const size_t square_size = 5;

        const float cube_cell_size = 0.25f;

        constexpr size_t window_width = board_width * square_size;
        constexpr size_t window_height = board_height * square_size;

    }

}

#endif

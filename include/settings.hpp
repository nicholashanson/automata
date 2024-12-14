#ifndef SETTINGS_H
#define SETTINGS_H

namespace conway {

    namespace settings {

        const size_t board_width = 5;
        const size_t board_height = 5;

        const size_t grid_size = 5;
        ;
        const size_t square_size = 5;

        constexpr size_t window_width = board_width * square_size;
        constexpr size_t window_height = board_height * square_size;

    }

}

#endif

#ifndef GLOBAL_ALIASES_HPP
#define GLOBAL_ALIASES_HPP

#include <settings.hpp>

namespace conway {

    // dimensions for board and under-lying cell-state storage
    using sim_mdspan = Kokkos::mdspan<bool, Kokkos::extents<size_t, settings::board_width + 2, settings::board_height + 2>>;
    using sim_array = std::array<bool, ( settings::board_width + 2 ) * ( settings::board_height + 2 ) >;

    // under-lying storage for cube faces
    static sim_array face_1;
    static sim_array face_2;
    static sim_array face_3;
    static sim_array face_4;
    static sim_array face_5;
    static sim_array face_6;
}

#endif

#ifndef GLOBAL_ALIASES_HPP
#define GLOBAL_ALIASES_HPP

#include <settings.hpp>

namespace conway {

    // dimensions for board and under-lying cell-state storage
    using sim_mdspan = Kokkos::mdspan<bool, Kokkos::extents<size_t, settings::board_width + 2, settings::board_height + 2>>;
    using sim_array = std::array<bool, ( settings::board_width + 2 ) * ( settings::board_height + 2 ) >;

}

#endif

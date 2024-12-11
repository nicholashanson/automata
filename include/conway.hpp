#ifndef CONWAY_HPP
#define CONWAY_HPP

// third-party includes
#include <mdspan-stable/include/mdspan/mdspan.hpp>

// standard library includes
#include <array>
#include <random>
#include <algorithm>

#include <settings.hpp>

namespace conway {

    // dimensions for various boards
    using md5x5 = Kokkos::mdspan<bool, Kokkos::extents<size_t, 5, 5>>; // 5x5 board
    using md6x6 = Kokkos::mdspan<bool, Kokkos::extents<size_t, 6, 6>>; // 6x6 board
    using md7x7 = Kokkos::mdspan<bool, Kokkos::extents<size_t, 7, 7>>; // 7x7 board
    using md7x8 = Kokkos::mdspan<bool, Kokkos::extents<size_t, 7, 8>>; // 7x8 board

    // dimensions for various cell-state arrays
    using a25 = std::array<bool, 25>; // 5x5 board
    using a36 = std::array<bool, 36>; // 6x6 board
    using a49 = std::array<bool, 49>; // 7x7 board
    using a56 = std::array<bool, 56>; // 7x8 board

    // dimensions for board and under-lying cell-state storage
    using sim_mdspan = Kokkos::mdspan<bool, Kokkos::extents<size_t, settings::board_width + 2, settings::board_height + 2>>;
    using sim_array = std::array<bool, ( settings::board_width + 2 ) * ( settings::board_height + 2 ) >;

    // arrays for testing evolve
    extern a25 rule_one_0_before;
    extern a25 rule_one_0_after;
    extern a25 rule_one_1_before;
    extern a25 rule_one_1_after;
    extern a25 rule_two_2_before;
    extern a25 rule_two_2_after;
    extern a49 rule_two_3_before;
    extern a49 rule_two_3_after;

    // arrays for testing padding update
    extern a49 board_update_before;
    extern a49 board_update_after;

    // under-lying storage for cell states
    static sim_array cell_states;

    // still-life state
    extern a36 block;
    extern a56 beehive;

}

// local includes
#include <board.hpp>
#include <evolve.hpp>
#include <seed.hpp>
#include <update_padding.hpp>

#endif

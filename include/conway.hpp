#ifndef CONWAY_HPP
#define CONWAY_HPP

// third-party includes
#include <mdspan-stable/include/mdspan/mdspan.hpp>

// standard library includes
#include <array>
#include <random>
#include <algorithm>
#include <iostream>

// local includes
#include <settings.hpp>
#include <board.hpp>
#include <board_bitset.hpp>
#include <board_set.hpp>
#include <board_unordered_set.hpp>
#include <cube.hpp>
#include <toroidal_cube_evolve.hpp>
#include <toroidal_cube.hpp>
#include <threaded_cube.hpp>
#include <thread_pool_cube.hpp>
#include <evolve_set.hpp>
#include <evolve.hpp>
#include <evolve_bitset.hpp>
#include <seed.hpp>
#include <update_padding.hpp>
#include <global_aliases.hpp>

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

    // arrays for testing evolve
    extern a25 rule_one_0_before;
    extern a25 rule_one_0_after;
    extern a25 rule_one_1_before;
    extern a25 rule_one_1_after;
    extern a25 rule_two_2_before;
    extern a25 rule_two_2_after;
    extern a49 rule_two_3_before;
    extern a49 rule_two_3_after;
    extern a49 blinker_period_0;
    extern a49 blinker_period_1;
    extern a49 blank_a49;

    // arrays for testing padding update
    extern a49 board_update_before;
    extern a49 board_update_after;

    // arrays for testing cube
    extern a25 blank_face;
    extern a25 cube_face_0_before_update;
    extern a25 cube_face_1_after_update;
    extern a25 cube_face_3_after_update;
    extern a25 cube_face_4_after_update;
    extern a25 cube_face_5_after_update;

    // under-lying storage for cell states
    static sim_array cell_states;

    // still-life state
    extern a36 block;
    extern a56 beehive;

}

#endif

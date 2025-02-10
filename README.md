# Game of Life

Simulates Cellular Automata, including Conway's Game of Life, in various formats.

## Tests

To build the tests:

```
build.bat --test
```
And run with:

```
ca_test
```

## Profiling 

To run the performance profiles, build with:

```
build.bat --profile
```
And run with:

```
ca_profile
```
## Compilation

C++23 is required. The code compiles on GCC 13.2.0.

Dependencies:
- boost test
- Kokkos mdspan
- raylib

Compiling with GCC 13.2.0 gives no warnings.

## Cube

The cube is a combination of six boards with spherical wrapping.

![cube](https://github.com/user-attachments/assets/c293ca2a-4e59-4f4e-9dd7-263688621c55)

## Cylinder

The cylinder is a single board with toroidal wrapping. 

![cylinder](https://github.com/user-attachments/assets/21d1126a-954d-4e6c-9db8-fa24b7224afd)

## Optimization

### Using std::bitset to speed-up evolution

```cpp
std::bitset<GRID_WIDTH * GRID_HEIGHT> edge_mask;

// set every bit in the edge-mask to '1'
edge_mask.set();

// clear each edge-cell
for ( j = 0; j < GRID_WIDTH; ++j ) {

  edge_mask.reset( j );                                      // zero-out the top row
  edge_mask.reset( ( GRID_HEIGHT - 1 ) * GRID_WIDTH + j );   // zero-out bottom row
}

for ( i = 0; i < GRID_HEIGHT; ++ i ) {

  edge_mask.reset( i * GRID_WIDTH );                         // zero-out left column
  edge_mask.reset( i * GRID_WIDTH + ( GRID_WIDTH - 1 ) );    // zero-out right column
}
```

![edge_mask](https://github.com/user-attachments/assets/58240447-7843-4112-9f84-f1edda1103a4)

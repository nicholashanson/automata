# Automata

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

<p align="center">
  <img src="https://github.com/user-attachments/assets/c293ca2a-4e59-4f4e-9dd7-263688621c55" alt="Cube" width="400" />
  &nbsp;&nbsp;&nbsp;&nbsp;
  <img src="https://github.com/user-attachments/assets/21d1126a-954d-4e6c-9db8-fa24b7224afd" alt="Cylinder" width="400" />
  <br />
  spherical cube and toroidal cylinder
</p>

## Padding

<p align="center">
  <img src="https://github.com/user-attachments/assets/46a258f7-8fd6-4c5f-8e0d-3b7cbe73bb15" width="400" />
</p>

Before we can evolve the grid to the next generation we need to update the grid padding. This is done once at the beginning of the siulation and then once again after
each generation. The grid padding is updated as follows:

( 1 ) Copy the second to last row of cell states into the first row:

```cpp
grid[ 0 ][ : ] = grid[ GRID_HEIGHT - 2 ][ : ]
```

<p align="center">
  <img src="https://github.com/user-attachments/assets/c7cc04e2-cf18-4afd-a956-b740f100f853" width="400" />
</p>

( 2 ) Copy the second row of cells states into the last row:

```cpp
grid[ GRID_HEIGHT - 1 ][ : ] = grid[ 1 ][ : ] 
```

<p align="center">
  <img src="https://github.com/user-attachments/assets/a4085064-03be-46e4-9212-dcdfbf26ecf6" width="400" />
</p>

( 3 ) Copy the second to last column of cells states into the first column:

```cpp
grid[ : ][ 0 ] = grid[ : ][ GRID_WIDTH - 2 ] 
```

<p align="center">
  <img src="https://github.com/user-attachments/assets/d0859a9d-21b8-415c-9b0f-88706da845ef" width="400" />
</p>


( 4 ) Copy the second column of cell states into the last column: 

```cpp
grid[ : ][ GRID_WIDTH - 1 ] = grid[ : ][ 1 ]
```

<p align="center">
  <img src="https://github.com/user-attachments/assets/a1db8d04-5312-4cf4-afcb-c5d4eabadcce" width="400" />
</p>

This creates the effect of toroidal wrapping.

## Evolution

To evolve the grid, we count the total number of cells in a nine-cell region and apply the evolution rules to the central cell in the region according to this count. We don't need to worry about grid wrapping because padding cells aren't targeted.
Compared with only counting live neigbors and applying rules conditionally based on whether the cell is live or dead, counting all the live cells in a nine-cell region simplifies evolution because there is less branching.

<p align="center">
  <img src="https://github.com/user-attachments/assets/053e567d-1dd7-48bb-bd20-2883e646b18c" width="600" />
</p>

## Optimization

### Using std::bitset to speed-up evolution

A cell is either active or inactive. "Active" means that the cells state could possibly change in the next generation. During the evolve stage, we count how many live cells there are in a nine-cell region. We then use this count to detemine the state of the central cell of this region in the next evolution. 
If the live-cell count is zero, we know that this cell has no possiblilty of changing in the next generation, so we don't need to check it. We can maintain a bitset of active cells that keeps track of which cells have a non-zero count and only check these cells in the next generation. 

If a cell becomes "inactive" ( there are no live cells in its nine cell-region ), we remove it from the set of active cells. If a cell becomes "active", we add it and all its neighbors to the set of active cells.

In the first evolution every cell needs to be checked:

```cpp
std::bitset<GRID_WIDTH * GRID_HEIGHT> active_cells;

active_cells.set();             // set every bit to '1'
```
Edge-cells are padding, so we need to remove them from active_cells. To do this we define a bit-mask called edge_mask:

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

Now we can do a bitwise AND between active_cells and edge_mask to remove the padding:

```cpp
active_cells &= edge_cells
```

<p align="center">
  <img src="https://github.com/user-attachments/assets/f0612ba7-a51d-4eff-be87-24b6bb1bdf1a" width="600" />
</p>

Now we need two more bitsets:

( 1 ) Activated cells: keeps track of all the dead cells that become live and their neighbors so they can be added to active_cells.

( 2 ) Deactivated cells: keeps track of any active cells that have zero live cells in their region. 

```cpp
std::bitset<GRID_WIDTH * GRID_HEIGHT> activated_cells;
std::bitset<GRID_WIDTH * GRID_HEIGHT> deactivated_cells;
```
In the case that cell 2 and cell 8 transition from dead to live, they and their neighbors are added to activated_cells. Activated cells are then added to active_cells using a bitwise OR:

```cpp
active_cells |= activated_cells
```
<p align="center">
  <img src="https://github.com/user-attachments/assets/89aeccc7-789a-47e7-be33-7edc79446b13" width="600" />
</p>

In the case that cell 9 dies it is added to deactivated_cells. Deactivated cells are then removed from active_cells using a bitwise XOR:

```cpp
active_cells ^= deactivated_cells
```
<p align="center">
  <img src="https://github.com/user-attachments/assets/6f791ceb-b805-482b-9544-e7214e5ab9f7" width="600" />
</p>

Finally, any padding cells that were added as neighbors of activated cells need to be removed using the edge_mask:

```cpp
active_cells &= edge_mask

```
<p align="center">
  <img src="https://github.com/user-attachments/assets/45e20b87-5830-4575-ad10-d4cffd1b37f8" width="600" />
</p>

Now we only need to check eight cells in the next iteration instead of all nine. In reality, most cells on the gird will be inactive, so speed-up will be significant.

<p align="center">
  <img src="performance_profiling/graphs/performance_evolve_bitset.png" />
</p>

The data above is collected by running the simulation for 400 iterations 40 times, and then caculating the average time taken to execute each iteration across all 40 runs. As can see from the graph, there is a small overhead incurred by tracking active cells at the very beginning of the simulation. In the case of bitset this overhead is much smaller than using a set ( in this case, std::unordered_set with perfect hashing ). Over the course of 400 iterations, bitset is at least 3x faster than the un-optimized approach and at least 50% faster than using std::unordered_set and doesn't have the massive initial overhead.

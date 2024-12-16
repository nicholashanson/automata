# Game of Life

### Compilation

C++23 is required. The code compiles on GCC 13.2.0.

Dependencies:
- boost test
- mdspan
- raylib

Compiling with GCC 13.2.0 gives the following warning:

`warning: passing 'const Vector3' as 'this' argument discards qualifiers [-fpermissive]`

### Cube

The cube is a combination of six boards with spherical wrapping.

![cube](https://github.com/user-attachments/assets/a127e0e5-7fd3-405d-937c-d61e9f8dceb9)

### Cylinder

The cylinder is a single board with toroidal wrapping. 

![cylinder](https://github.com/user-attachments/assets/21d1126a-954d-4e6c-9db8-fa24b7224afd)

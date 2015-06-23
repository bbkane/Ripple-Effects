# Ripple-Effects
Ripple-Effects (Advanced Game Programming Final Project) with a shiny cmake build system

Zip folder for the game is [here](https://github.com/bbk1524/Ripple-Effects/releases)

## Dependencies

### Windows
- cmake 3.1

### Mac
- cmake 3.1
- homebrew
- xquartz (for liquidfun)

Use homebrew to install the following dependencies

- sdl2
- sdl2_gfx
- sdl2_image
- sdl2_mixer
- sdl2_ttf

Make sure the paths in the root CMakeLists.txt file match with the output of `sdl2-config --cflags --libs`.
A `find_path` argument should be the result of `sdl2-config --cflags`.
A `find_library` argument should be the result of `sdl2-config --libs`

### Linux

- cmake 3.1 (the version in the Ubuntu repos is currently 3.0, and I had to install it from the
        cmake website)

- libsdl2-dev
- libsdl2-gfx-dev (may not be necessary)
- libsdl2-image-dev
- libsdl2-mixer-dev
- libsdl2-ttf-dev

Make sure the paths in the root CMakeLists.txt file match with the output of `sdl2-config --cflags --libs`.
A `find_path` argument should be the result of `sdl2-config --cflags`.
A `find_library` argument should be the result of `sdl2-config --libs`


# This doesn't work with VS2015 RC, but will with VS2013

# I just changed this to 3.0 for Ubuntu. Hope it works
# I need 3.1 for CXX version
cmake_minimum_required(VERSION 3.1)

# Solution name
project(Ripple_Effects)

# Find dynamic libraries
# include dynamic libraries with:
# include_directories(<target_name> ${<dynamic_library_name>_INCLUDE_DIR})
# link dynamic libraries with:
# target_link_libraries(<target_name> ${<dynamic_library_name>_INCLUDE_DIR})

# Find SDL2

set(SDL2_WIN "${CMAKE_SOURCE_DIR}/Dynamic-Libraries/SDL2-2.0.3")
set(SDL2_INCLUDE_LINUX "/usr/include/SDL2")
set(SDL2_LIB_LINUX "/usr/lib/x86_64-linux-gnu")
find_path(SDL2_INCLUDE_DIR SDL.h
    PATHS
    "${SDL2_WIN}/include"
    "/usr/local/include/SDL2"
    "${SDL2_INCLUDE_LINUX}"
)
find_library(SDL2_LIBRARY NAMES SDL2
    PATHS
    "${SDL2_WIN}/lib/x86/"
    "/usr/local/lib"
    "${SDL2_LIB_LINUX}"
)
find_library(SDL2MAIN_LIBRARY NAMES SDL2main
    PATHS
    "${SDL2_WIN}/lib/x86/"
    "/usr/local/lib"
    "${SDL2_LIB_LINUX}"
)

# SDL2_image
set(SDL2_IMAGE_WIN "${CMAKE_SOURCE_DIR}/Dynamic-Libraries/SDL2_image-2.0.0")
find_path(SDL2_IMAGE_INCLUDE_DIR SDL_image.h
    PATHS
    "${SDL2_IMAGE_WIN}/include"
    "/usr/local/include/SDL2"
    "${SDL2_INCLUDE_LINUX}"
)
find_library(SDL2_IMAGE_LIBRARY NAMES SDL2_image
    PATHS
    "${SDL2_IMAGE_WIN}/lib/x86"
    "/usr/local/lib"
    "${SDL2_LIB_LINUX}"
)

# SDL2_mixer
set(SDL2_MIXER_WIN "${CMAKE_SOURCE_DIR}/Dynamic-Libraries/SDL2_mixer-2.0.0")
find_path(SDL2_MIXER_INCLUDE_DIR SDL_mixer.h
    PATHS
    "${SDL2_MIXER_WIN}/include"
    "/usr/local/include/SDL2"
    "${SDL2_INCLUDE_LINUX}"
)
message(**********************${SDL2_MIXER_INCLUDE_DIR})
find_library(SDL2_MIXER_LIBRARY NAMES SDL2_mixer
    PATHS
    "${SDL2_MIXER_WIN}/lib/x86"
    "/usr/local/lib"
    "${SDL2_LIB_LINUX}"
)

# SDL2_ttf
set(SDL2_TTF_WIN "${CMAKE_SOURCE_DIR}/Dynamic-Libraries/SDL2_ttf-2.0.12")
find_path(SDL2_TTF_INCLUDE_DIR SDL_ttf.h
    PATHS
    "${SDL2_TTF_WIN}/include"
    "/usr/local/include/SDL2"
    "${SDL2_INCLUDE_LINUX}"
)
find_library(SDL2_TTF_LIBRARY NAMES SDL2_ttf
    PATHS
    "${SDL2_TTF_WIN}/lib/x86"
    "/usr/local/lib"
    "${SDL2_LIB_LINUX}"
)

# Find static libraries (no dlls).
# Include with:
# include_directories(<target_name> ${<static_library_name>_SOURCE_DIR})
# Link with:
# target_link_libraries(<target_name> <static_library_name>) #no ${} needed

# Add tinyXML
add_subdirectory(Static-Libraries/tinyxml EXCLUDE_FROM_ALL)

# Add Box2D. Using the LiquidFun version instead
# add_subdirectory(Static-Libraries/Box2D_v2.1.2/Box2D EXCLUDE_FROM_ALL)

# Add LiquidFun version of Box2D
add_subdirectory(Static-Libraries/liquidfun-1.1.0/liquidfun/Box2D EXCLUDE_FROM_ALL)

# Add SDL2_gfx
add_subdirectory(Static-Libraries/SDL2_gfx EXCLUDE_FROM_ALL)

# Add Project Folder
add_subdirectory(Source)

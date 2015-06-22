project(SDL2_gfx)
include_directories(./SDL2_gfx-1.0.1 ${SDL2_INCLUDE_DIR})
add_library(SDL2_gfx STATIC
	SDL2_gfx-1.0.1/SDL2_framerate.c
	SDL2_gfx-1.0.1/SDL2_framerate.h
	SDL2_gfx-1.0.1/SDL2_gfxPrimitives.c
	SDL2_gfx-1.0.1/SDL2_gfxPrimitives.h
	SDL2_gfx-1.0.1/SDL2_gfxPrimitives_font.h
	SDL2_gfx-1.0.1/SDL2_imageFilter.c
	SDL2_gfx-1.0.1/SDL2_imageFilter.h
	SDL2_gfx-1.0.1/SDL2_rotozoom.c
	SDL2_gfx-1.0.1/SDL2_rotozoom.h
)
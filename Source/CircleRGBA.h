#include "SDL.h"
#include "SDL2_gfx-1.0.1\SDL2_gfxPrimitives.h"
#include "GraphicsDevice.h"

class CircleRGBA {
public:
	bool Initialize(SDL_Renderer *, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
	void Draw(Sint16 x, Sint16 y, Sint16 rad);
protected:
	SDL_Renderer * ren;
	Uint8 r;
	Uint8 g;
	Uint8 b;
	Uint8 a;
};
#include "CircleRGBA.h"
#include <iostream>

bool CircleRGBA::Initialize(SDL_Renderer * ren, Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
	this->ren = ren; 
	this->r = r; this->a = a; this->g = g; this->b = b; this->a = a;
	return true;
}

void CircleRGBA::Draw(Sint16 x, Sint16 y, Sint16 rad) {
	//Store renderer's drawing values
	Uint8 r_old, g_old, b_old, a_old;
	if(SDL_GetRenderDrawColor(ren, &r_old, &g_old, &b_old, &a_old) != 0) {
		std::cerr << __FUNCTION__ << " Error saving renderer's stuff " << std::endl;
	}
	//draw circle
	aacircleRGBA(ren, x, y, rad, r, g, b, a);
	
	//Restore renderer's values
	SDL_SetRenderDrawColor(ren, r_old, g_old, b_old, a_old);
}
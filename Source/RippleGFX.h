#ifndef RIPPLE_GFX_H
#define RIPPLE_GFX_H

#include"Component.h"
class Actor;
class GraphicsDevice;
class CircleRGBA;
class View;
class MusicAssetLibrary;

typedef signed __int16 Sint16; //copying from SDL
typedef unsigned __int32 Uint32;

class RippleGFX : public Component
{
public:
	RippleGFX(std::shared_ptr<Actor>);
	~RippleGFX();
	void Initialize(GraphicsDevice*,MusicAssetLibrary* , View* , Sint16, Sint16); //should I construct the circle from inside?
	void Start();
	void Update();
	void Finish();
	void Draw();
	void Present();
	int GetX();
	int GetY();
	int GetR();

//protected:
	CircleRGBA* circle;
	GraphicsDevice* gDevice;
	MusicAssetLibrary* mLibrary;
	View* view;
	Sint16 x;
	Sint16 y;
	Sint16 r;
	b2Timer lifeTime;
};


#endif
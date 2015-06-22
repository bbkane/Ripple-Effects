#include "Box2DDebugDraw.h"
#include "SDL2_gfx-1.0.1\SDL2_gfxPrimitives.h"

Box2DDebugDraw::Box2DDebugDraw() {
	circleAccuracy = 9;
}

Box2DDebugDraw::~Box2DDebugDraw() {
	gDevice = NULL;
}

bool Box2DDebugDraw::Initialize(GraphicsDevice* gDevice) {
	if(gDevice == NULL)
	{
		return false;
	}
	this->gDevice = gDevice;
	return true;
}

void Box2DDebugDraw::DrawPolygon(const b2Vec2 *vertices, int32 vertexCount, const b2Color &color) 
{
 //  	// Draw Shape Vertices using SDL2_gfx (Red)
 //   SDL_SetRenderDrawColor(gDevice->GetRenderer(),0,255,0,255);

	//// Draw Bound Box Vertices using SDL2 Primitives
	//for(int i=0; i<(vertexCount-1); i++) {
 //       lineRGBA(gDevice->GetRenderer(),PW2RW(vertices[i].x),PW2RW(vertices[i].y),PW2RW(vertices[i+1].x),PW2RW(vertices[i+1].y),0,255,0,100);
	//	//SDL_RenderDrawLine(gDevice->GetRenderer(),PW2RW(vertices[i].x),PW2RW(vertices[i].y),PW2RW(vertices[i+1].x),PW2RW(vertices[i+1].y));
	//}	
	////draw a line from the last to the first
 //   lineRGBA(gDevice->GetRenderer(),PW2RW(vertices[vertexCount-1].x),PW2RW(vertices[vertexCount-1].y),PW2RW(vertices[0].x),PW2RW(vertices[0].y),0,255,0,100);

 //   //Reset color (black)
 //   SDL_SetRenderDrawColor(gDevice->GetRenderer(),0,0,0,255);
}

void Box2DDebugDraw::DrawSolidPolygon(const b2Vec2 *vertices, int32 vertexCount, const b2Color &color)
{
   	// Draw Bound Box Vertices using SDL2 Primitives (Green)
    SDL_SetRenderDrawColor(gDevice->GetRenderer(),0,255,0,255);

	// Draw Bound Box Vertices using SDL2 Primitives
	for(int i=0; i<(vertexCount-1); i++) {
        lineRGBA(gDevice->GetRenderer(),PW2RW(vertices[i].x),PW2RW(vertices[i].y),PW2RW(vertices[i+1].x),PW2RW(vertices[i+1].y),255,0,0,100);
		//SDL_RenderDrawLine(gDevice->GetRenderer(),PW2RW(vertices[i].x),PW2RW(vertices[i].y),PW2RW(vertices[i+1].x),PW2RW(vertices[i+1].y));
	}	
	//draw a line from the last to the first
    lineRGBA(gDevice->GetRenderer(),PW2RW(vertices[vertexCount-1].x),PW2RW(vertices[vertexCount-1].y),PW2RW(vertices[0].x),PW2RW(vertices[0].y),255,0,0,100);

    //Reset color (black)
    SDL_SetRenderDrawColor(gDevice->GetRenderer(),0,0,0,255);
}

void Box2DDebugDraw::DrawCircle(const b2Vec2 &center, float32 radius, const b2Color &color) 
{
	//Unimplemented
}

void Box2DDebugDraw::DrawSolidCircle(const b2Vec2 &center, float32 radius, const b2Vec2 &axis, const b2Color &color)
{
    //Unimplemented
}

void Box2DDebugDraw::DrawSegment(const b2Vec2 &p1, const b2Vec2 &p2, const b2Color &color) 
{
	// Draw Bound Box Vertices using SDL2 Primitives (Green)
    SDL_SetRenderDrawColor(gDevice->GetRenderer(),0,255,0,255);

	// Draw Bound Box Vertices using SDL2 Primitives

	//draw a line from the last to the first
    lineRGBA(gDevice->GetRenderer(),PW2RW(p1.x),PW2RW(p1.y),PW2RW(p2.x),PW2RW(p2.y),255,0,0,100);

    //Reset color (black)
    SDL_SetRenderDrawColor(gDevice->GetRenderer(),0,0,0,255);
}

void Box2DDebugDraw::DrawTransform(const b2Transform &xf) 
{
    //Unimplemented
}
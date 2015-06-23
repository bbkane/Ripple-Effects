/*
* Author:	Keith Bush
*			UALR
* 
* Date:		January 31, 2015	
*
* File:		GraphicsDevice.cpp
*
* Purpose:	Definition of the SDL GraphicsDevice class
*/

#include<iostream>
#include "GraphicsDevice.h"
#include "SDL2_gfx-1.0.1/SDL2_gfxPrimitives.h"
#include "Definitions.h"
#include <array>
GraphicsDevice::GraphicsDevice(Uint32 width, Uint32 height) : SCREEN_WIDTH(width), SCREEN_HEIGHT(height)
{
	screen = NULL;
	renderer = NULL;
}

GraphicsDevice::~GraphicsDevice()
{
	if(!ShutDown())
	{
		printf( "SDL could not shut down! SDL_Error: %s\n", SDL_GetError() );
		exit(1);
	}
}

SDL_Window* GraphicsDevice::GetWindow()
{
	return(screen);
}

bool GraphicsDevice::Initialize(bool fullScreen)
{

	//Initialize all SDL subsystems
	if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
		return(false);
	}

	//Initialize SDL_image subsystems
	if(!IMG_Init(IMG_INIT_PNG))
	{
		printf( "SDL_image could not initialize! SDL_Error: %s\n", IMG_GetError() );
		return(false);
	}

	//Initialize SDL_ttf subsystems
	if(TTF_Init()==-1)
	{
		printf( "SDL_ttf could not initialize! SDL_Error: %s\n", TTF_GetError() );
		return(false);
	}
	font = TTF_OpenFont( "./Assets/Fonts/impact.ttf", 48 );
    if( font == NULL )
	{
        printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
	}
	if(fullScreen)
	{
		//Construct and check window construction
		screen = SDL_CreateWindow("Demonstration Window",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_FULLSCREEN);
	}
	else
	{
		screen = SDL_CreateWindow("Ripple Effects",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	}
	if(screen==NULL)
	{
		printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
		return(false);
	}

	//Construct the renderer
	renderer = SDL_CreateRenderer(screen,-1,SDL_RENDERER_ACCELERATED);
	if(renderer==NULL)
	{
		printf( "Renderer could not be created! SDL_Error: %s\n", SDL_GetError() );
		return(false);
	}

	//Set the background color (default)
	SDL_SetRenderDrawColor(renderer,0,0,255,155);

	return(true);

}

bool GraphicsDevice::ShutDown()
{
	//Free the window
	SDL_DestroyWindow(screen);
	screen = NULL;

	//Free renderer
	SDL_DestroyRenderer(renderer);
	renderer = NULL;

	//Quit SDL Subsystems
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();

	return(true);
}



void GraphicsDevice::Begin()
{
	//fills screen with SDL_RenderDrawColor's pixels
	SDL_SetRenderDrawColor(renderer,0,0,255,155); //a lovely blue color :)
	SDL_RenderClear(renderer);
}

void GraphicsDevice::Draw(std::string message, std::vector<b2Vec2> *leftBank, std::vector<b2Vec2> *rightBank)
{
	DrawBanks(leftBank, rightBank);

	for(auto sprite : sprites)
	{
		sprite->Draw();
	}

	for(auto ripple: ripples) {
		ripple->Draw();
	}

	DrawFonts(message); //the score
}

void GraphicsDevice::DrawFonts(std::string message) {
	TTF_Font *font = TTF_OpenFont( "./Assets/Fonts/impact.ttf", 48 );
    if( font == NULL )
	{
        printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
	}

	SDL_Color textColor = { 255, 255, 51 };
	SDL_Texture* textSheetTexture = SDL_CreateTextureFromSurface( renderer,  TTF_RenderText_Solid(font, message.c_str(), textColor));

	//Set rendering space and render to screen
	int width=0,height=0;
	SDL_QueryTexture(textSheetTexture,NULL,NULL,&width,&height);
	SDL_Rect renderQuad = {10, 10, width, height};

	//Render to screen
	SDL_RenderCopy(renderer, textSheetTexture, NULL, &renderQuad );
}

void GraphicsDevice::Present()
{
	SDL_RenderPresent(renderer);
}

void GraphicsDevice::DrawBanks(std::vector<b2Vec2> *leftBank, std::vector<b2Vec2> *rightBank) {
	// Save Color
	Uint8 r, g, b, a;
	SDL_GetRenderDrawColor(GetRenderer(),&r, &g, &b, &a);


	Sint16 vx[4];
	Sint16 vy[4];
	//get points of each polygon
	for(auto i = leftBank->begin();(i + 1) != leftBank->end(); i++) {
		vx[0] = PW2RW(0);
		vy[0] = PW2RW(i->y);
		vx[1] = PW2RW(i->x);
		vy[1] = PW2RW(i->y);
		vx[2] = PW2RW((i+1)->x);
		vy[2] = PW2RW((i+1)->y);
		vx[3] = PW2RW(0);
		vy[3] = PW2RW((i+1)->y);
		filledPolygonRGBA(renderer,
			vx, vy,
			4,
			0, 100, 0, 255);
	}

	for(auto i = rightBank->begin();(i + 1) != rightBank->end(); i++) {
		vx[0] = PW2RW(i->x);
		vy[0] = PW2RW(i->y);
		vx[1] = PW2RW(SCREEN_WIDTH);
		vy[1] = PW2RW(i->y);
		vx[2] = PW2RW(SCREEN_WIDTH);
		vy[2] = PW2RW((i+1)->y);
		vx[3] = PW2RW((i+1)->x);
		vy[3] = PW2RW((i+1)->y);
		filledPolygonRGBA(renderer,
			vx, vy,
			4,
			0, 100, 0, 255);
	}


	//Reset color
	SDL_SetRenderDrawColor(GetRenderer(),r, g, b, a);
}

SDL_Renderer* GraphicsDevice::GetRenderer()
{
	return(renderer);
}

void GraphicsDevice::AddSprite(Sprite* sprite)
{
	sprites.push_back(sprite);
}

void GraphicsDevice::AddRippleGFX(RippleGFX* ripple) {
	ripples.push_back(ripple);
}

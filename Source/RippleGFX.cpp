#include "Definitions.h"
#include "GraphicsDevice.h"
#include "Actor.h"
#include "Component.h"
#include "RippleGFX.h"
#include "RigidBody.h"
#include "CircleRGBA.h"
#include "View.h"
#include <SDL_mixer.h>
#include "MusicAssetLibrary.h"

RippleGFX::RippleGFX(std::shared_ptr<Actor> owner) : Component(owner)
{
	gDevice = NULL;
}

RippleGFX::~RippleGFX(){}

void RippleGFX::Initialize(GraphicsDevice* gDevice, MusicAssetLibrary* mLibrary, View* view, Sint16 x, Sint16 y)
{
	this->gDevice = gDevice;
	this->mLibrary = mLibrary; //want some music?

	this->lifeTime = b2Timer();
	this->view = view;

	this->x = x;
	this->y = y;
	this->r = 100; //I should make this part of the init, so I can spawn different size ripples
	this->circle = new CircleRGBA();
	circle->Initialize(gDevice->GetRenderer(), 255, 255, 255, 150);
	//Add RippleGFX to gDevice
	gDevice->AddRippleGFX(this);
	Mix_PlayChannel( -1,mLibrary->search("splash"),0 ); //sound effects yay
}

void RippleGFX::Start(){}

void RippleGFX::Update(){}

void RippleGFX::Finish(){}

void RippleGFX::Draw()
{
	if(_owner->GetIsAlive() && lifeTime.GetMilliseconds() <= 200) { //hardcodign for simplicity
		circle->Draw(this->x, this->y, this->r);
	}
}

int RippleGFX::GetX() {return x;}
int RippleGFX::GetY() {return y;}
int RippleGFX::GetR() {return r;}
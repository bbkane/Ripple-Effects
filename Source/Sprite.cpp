#include "Definitions.h"
#include "GraphicsDevice.h"
#include "Actor.h"
#include "Component.h"
#include "Sprite.h"
#include "RigidBody.h"
#include "Texture.h"
#include "View.h"

Sprite::Sprite(std::shared_ptr<Actor> owner) : Component(owner)
{
	texture = NULL;
	gDevice = NULL;
}

Sprite::~Sprite(){}

void Sprite::Initialize(GraphicsDevice* gDevice, Texture* texture, View* view)
{
	this->gDevice = gDevice;

	//Load the Art Asset
	this->texture = texture;

	this->view = view;

	//Add Sprite to gDevice
	gDevice->AddSprite(this);

	isAlive= true;
}

void Sprite::Start(){}

void Sprite::Update(){}

void Sprite::Finish(){}

void Sprite::Draw()
{
	//Check if the owner is alive before drawing (this won't work in update)
	if(_owner->GetIsAlive()) { 
		//Convert Physics World Position to Render World Position
		std::shared_ptr<RigidBody> body = _owner->GetComponent<RigidBody>();

		//Extract position and angle
		b2Vec2 position = body->GetPosition();
		float32 angle = body->GetAngle();
		float drawX = PW2RW(position.x) - texture->getWidth()/2.0f + view->getX(); 
		float drawY = PW2RW(position.y) - texture->getHeight()/2.0f + view->getY();
		float drawAngle = PW2RWAngle(angle);

		//Render to the Screen
		texture->renderEx(gDevice->GetRenderer(),(int)drawX,(int)drawY,drawAngle,NULL);
	}
}

bool Sprite::GetIsAlive() {return this->isAlive;}
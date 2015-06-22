#include"Definitions.h"
#include"PlayerBehavior.h"
#include"RigidBody.h"
#include "InputDevice.h"

#include "CircleRGBA.h"
#include "Game.h"

#include "ResourceManager.h"

PlayerBehavior::PlayerBehavior(std::shared_ptr<Actor> owner) : Component(owner){}

PlayerBehavior::~PlayerBehavior(){}

void PlayerBehavior::Initialize(ResourceManager* resourceManager, InputDevice* iDevice, float dt)
{
	this->dt = dt;
	this->iDevice = iDevice;
	this->resourceManager = resourceManager;
	this->timer = b2Timer();
}

void PlayerBehavior::Start(){}

void PlayerBehavior::Update()
{
	//only allow 10 times a second
	if(this->iDevice->getEvent(LEFT_MOUSE_DOWN) && timer.GetMilliseconds() > 100) {
		ActorInfo actorInfo;
		actorInfo.name = "Ripple";
		actorInfo.x = iDevice->getX();
		actorInfo.y = iDevice->getY();
		actorInfo.angle = 30;
		resourceManager->MarkForCreation(actorInfo);
		timer.Reset();
	}
	if(this->iDevice->getEvent(RIGHT_MOUSE_DOWN)) {
		ActorInfo actorInfo;
		actorInfo.name = "Dock";
		actorInfo.x = iDevice->getX();
		actorInfo.y = iDevice->getY();
		actorInfo.angle = 0;
		resourceManager->MarkForCreation(actorInfo);
	}
}

void PlayerBehavior::Finish(){}

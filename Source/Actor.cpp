#include "Definitions.h"
#include "GraphicsDevice.h"
#include "Actor.h"
#include "RigidBody.h"
#include "Sprite.h"
#include "BarrelBehavior.h"
#include "CarrierBehavior.h"
#include "PlayerBehavior.h"
#include "PhysicsAssetLibrary.h"
#include "Game.h"
#include "RippleGFX.h"
#include "RipplePhysics.h"

Actor::Actor()
{
	initialized = false;
}

Actor::~Actor()
{

}

bool Actor::Initialize(Game* game, std::string name, float x, float y, float angle) {
	//Initialize each actor according to it's name

	//Create Components
	if(name =="Barrel") {

		std::shared_ptr<RigidBody> body = std::make_shared<RigidBody>(shared_from_this());
		std::shared_ptr<BarrelBehavior> behavior = std::make_shared<BarrelBehavior>(shared_from_this());
		std::shared_ptr<Sprite> sprite = std::make_shared<Sprite>(shared_from_this());

		body->Initialize(game->world, game->aLibrary->search(name), game->pLibrary->search(name),name, x, y, angle);
		sprite->Initialize(game->gDevice,game->aLibrary->search(name), game->view);
		behavior->Initialize(game->leftBank, game->rightBank,game->mLibrary,&game->score,game->dt);

		//Add Components to body
		AddComponent(body);
		AddComponent(sprite);
		AddComponent(behavior);
	} else if (name == "Carrier") {
		std::shared_ptr<RigidBody> body = std::make_shared<RigidBody>(shared_from_this());
		std::shared_ptr<CarrierBehavior> behavior = std::make_shared<CarrierBehavior>(shared_from_this());
		std::shared_ptr<Sprite> sprite = std::make_shared<Sprite>(shared_from_this());

		body->Initialize(game->world, game->aLibrary->search(name), game->pLibrary->search(name),name, x, y, angle);
		sprite->Initialize(game->gDevice,game->aLibrary->search(name), game->view);
		behavior->Initialize(game->randomGen, game->dt);

		//Add Components to body
		AddComponent(body);
		AddComponent(sprite);
		AddComponent(behavior);
	} else if (name == "Player") {
		//std::shared_ptr<RigidBody> body = std::make_shared<RigidBody>(shared_from_this());
		std::shared_ptr<PlayerBehavior> behavior = std::make_shared<PlayerBehavior>(shared_from_this());
		//std::shared_ptr<Sprite> sprite = std::make_shared<Sprite>(shared_from_this());

		//body->Initialize(game->world, game->aLibrary->search(name), game->pLibrary->search(name), x, y, angle);
		//sprite->Initialize(game->gDevice,game->aLibrary->search(name), game->view);
		behavior->Initialize(game->resourceManager, game->iDevice, game->dt);

		AddComponent(behavior);
	} else if (name == "Ripple") {
		std::shared_ptr<RippleGFX> ripple = std::make_shared<RippleGFX>(shared_from_this());
		std::shared_ptr<RipplePhysics> ripplephysics = std::make_shared<RipplePhysics>(shared_from_this());

		ripple->Initialize(game->gDevice, game->mLibrary,game->view, x,y);//replace this with mouse stuff
		ripplephysics->Initialize(game->world);

		AddComponent(ripple);
		AddComponent(ripplephysics);

	} else if (name == "Rock") {
		std::shared_ptr<RigidBody> body = std::make_shared<RigidBody>(shared_from_this());
		std::shared_ptr<Sprite> sprite = std::make_shared<Sprite>(shared_from_this());

		body->Initialize(game->world, game->aLibrary->search(name), game->pLibrary->search(name),name, x, y, angle);
		sprite->Initialize(game->gDevice,game->aLibrary->search(name), game->view);

		//Add Components to body
		AddComponent(body);
		AddComponent(sprite);
	}
	else if(name == "Dock") {
		std::shared_ptr<RigidBody> body = std::make_shared<RigidBody>(shared_from_this());
		std::shared_ptr<Sprite> sprite = std::make_shared<Sprite>(shared_from_this());

		body->Initialize(game->world, game->aLibrary->search(name), game->pLibrary->search(name),name, x, y, angle);
		sprite->Initialize(game->gDevice,game->aLibrary->search(name), game->view);

		//Add Components to body
		AddComponent(body);
		AddComponent(sprite);
	}
	else {
		std::cerr << __FUNCTION__ << " : " << name << " not found" << std::endl;
	}

	//Call the start method
	if(!initialized)
	{
		for(auto comp : components)
		{
			comp->Start();
		}
		initialized = true;
	}
	this->isAlive = true;
	this->name = name;
	return(initialized);
}

std::string Actor::GetName() {
	return name;
}

bool Actor::GetIsAlive() {
	return this->isAlive;
}
void Actor::SetIsAlive(bool alive) {
	this->isAlive = alive;
}
void Actor::Update()
{
	for(auto comp : components)
	{
		comp->Update();
	}
}

void Actor::AddComponent(std::shared_ptr<Component> component)
{
	components.push_back(component);
}
#include "ResourceManager.h"

#include "Game.h"
#include "Actor.h"

//Resource Manager handles the orderly adding and removal of objects to the world

bool ResourceManager::Initialize(Game* game) {
	this->game = game;
	return true;
}

void ResourceManager::MarkForCreation(ActorInfo actorInfo) {
	actorsToCreate.push_back(actorInfo);
}

bool ResourceManager::AddToActors() {
	for(auto ai: actorsToCreate) {
		std::shared_ptr<Actor> object = std::make_shared<Actor>();
		if(object->Initialize(game, ai.name, ai.x, ai.y, ai.angle)) {
			actors.push_back(object);
		} else {
			std::cerr << "Error creating object" << std::endl;
			return false;
		}
	}
	actorsToCreate.clear();
	return true;
}

void ResourceManager::UpdateActors() {
	for(auto a: actors) {
		a->Update();
	}
}

void ResourceManager::RemoveFromActors() {
	actors.erase( std::remove_if(actors.begin(), actors.end(), [](std::shared_ptr<Actor> a) {return !a->GetIsAlive();}), actors.end());
}
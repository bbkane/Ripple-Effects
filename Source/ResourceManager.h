#ifndef RESOURCE_MANAGER
#define RESOURCE_MANAGER

#include "Definitions.h"
#include <vector>
#include <memory>

//This class's ONLY JOB is to manipulate actors. Other classes will pass it ActorInfo that will get put on a queue,
//and it will add to actors there. then it will update actors, then it will delete from actors. That's it.

class Game;
class Actor;

class ResourceManager {
public:
	bool Initialize(Game* game);
	void MarkForCreation(ActorInfo);
	bool AddToActors();
	void UpdateActors();
	void RemoveFromActors();
private:
	std::vector<std::shared_ptr<Actor>> actors;
	std::vector<ActorInfo> actorsToCreate;
	Game* game;
};

#endif
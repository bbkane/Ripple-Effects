#include "PhysicsAssetLibrary.h"


//From Definitions.h
//typedef struct GamePhysics {
//	GAME_FLT density;
//	GAME_FLT restitution;
//	GAME_FLT angularDamping;
//	GAME_FLT linearDamping;
//	GAME_FLT angularForce;
//	GAME_FLT linearForce;
//	GAME_FLT friction;
//	std::string type;
//	std::string shape;
//} GamePhysics;


bool PhysicsAssetLibrary::initialize() {
	library["Player"].density = 0.1f;
	library["Player"].restitution = 0.7f;
	library["Player"].angularDamping = 0.9f;
	library["Player"].linearDamping = 0.9f;
	library["Player"].angularForce = 0.1f;
	library["Player"].linearForce = 5.0f;
	library["Player"].friction = 0.9f;
	library["Player"].type = "dynamic";
	library["Player"].shape = "circle";

	library["Barrel"].density = 0.19f;
	library["Barrel"].restitution = 0.3f;
	library["Barrel"].angularDamping = 0.5f;
	library["Barrel"].linearDamping = 0.5f;
	library["Barrel"].angularForce = 0.2f;
	library["Barrel"].linearForce = 0.6f;
	library["Barrel"].friction = 0.5f;
	library["Barrel"].type = "dynamic";
	library["Barrel"].shape = "circle";

	library["Rock"].density = 0.1f;
	library["Rock"].restitution = 0.5f;
	library["Rock"].angularDamping = 0.1f;
	library["Rock"].linearDamping = 0.1f;
	library["Rock"].angularForce = 0.2f;
	library["Rock"].linearForce = 0.6f;
	library["Rock"].friction = 0.5f;
	library["Rock"].type = "static";
	library["Rock"].shape = "circle";

	library["Dock"].density = 0.1f;
	library["Dock"].restitution = 0.5f;
	library["Dock"].angularDamping = 0.1f;
	library["Dock"].linearDamping = 0.1f;
	library["Dock"].angularForce = 0.2f;
	library["Dock"].linearForce = 0.6f;
	library["Dock"].friction = 0.5f;
	library["Dock"].type = "static";
	library["Dock"].shape = "rectangle";

	library["Carrier"].density = 0.19f;
	library["Carrier"].restitution = 0.3f;
	library["Carrier"].angularDamping = 0.1f;
	library["Carrier"].linearDamping = 0.1f;
	library["Carrier"].angularForce = 0.2f;
	library["Carrier"].linearForce = 0.1f;
	library["Carrier"].friction = 0.5f;
	library["Carrier"].type = "dynamic";
	library["Carrier"].shape = "rectangle";

	library["Bullet"].density = 0.1f;
	library["Bullet"].restitution = 0.9f;
	library["Bullet"].angularDamping = 0.1f;
	library["Bullet"].linearDamping = 0.1f;
	library["Bullet"].angularForce = 0.2f;
	library["Bullet"].linearForce = 0.6f;
	library["Bullet"].friction = 0.5f;
	library["Bullet"].type = "dynamic";
	library["Bullet"].shape = "rectangle";

	return true;
}

GamePhysics PhysicsAssetLibrary::search(std::string name) {
	if(library.count(name)) {
		return library[name];
	}
	else {
		std::cerr << __FUNCTION__ << " : GamePhysics for " << name << " not found" << std::endl;
		GamePhysics nil = {0,0,0,0,0,0,0,"nada","nothing"};
		return nil;
	}
}
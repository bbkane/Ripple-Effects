#ifndef PHYSICS_ASSET_LIBRARY_H
#define PHYSICS_ASSET_LIBRARY_H

#include "Definitions.h"

#include <map>
#include <iostream>

class PhysicsAssetLibrary {
public:
	bool initialize();
	GamePhysics search(std::string);

private:
	std::map<std::string, GamePhysics> library;
};
#endif

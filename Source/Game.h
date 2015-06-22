#ifndef GAME_H
#define GAME_H

#include "Definitions.h"
#include "ArtAssetLibrary.h"
#include "PhysicsAssetLibrary.h"
#include "GraphicsDevice.h"
#include "InputDevice.h"
#include "View.h"
#include "Timer.h"
#include "tinyxml/tinystr.h"
#include "tinyxml/tinyxml.h"

#include <Box2D\Box2D.h>
#include "Box2DDebugDraw.h"
#include <vector>
#include <iostream>
#include <string>
#include <random>
class MusicAssetLibrary;
class Actor;
class ResourceManager;

class Game {
	friend class Actor; //Actor needs Games stuff
public:
	bool initialize(GraphicsDevice* gDevice, InputDevice* iDevice, GAME_INT fps);
	bool loadLevel(std::string configFile);
	void run();
	void update();
	bool destroy();
protected:
	ResourceManager * resourceManager;
	GAME_INT score;
	GAME_FLT dt;
	Timer timer;
	GraphicsDevice* gDevice;
	InputDevice* iDevice;
	ArtAssetLibrary* aLibrary;
	PhysicsAssetLibrary* pLibrary;
	MusicAssetLibrary* mLibrary;
	View* view;
	std::mt19937* randomGen;
	b2World* world;
	b2Timer barrelTimer;
	Box2DDebugDraw* debugDraw;
	std::vector<b2Vec2>* leftBank;
	std::vector<b2Vec2>* rightBank;
};
#endif
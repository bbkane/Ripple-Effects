#include "Game.h"

#include "Actor.h"
#include "MusicAssetLibrary.h"
#include "ResourceManager.h"
#include "MyContactListener.h"

bool Game::initialize(GraphicsDevice* gDevice,InputDevice* iDevice, GAME_INT fps) {

	//make dt
	this->dt = 1.0f/ fps;

	this->score = 0;

	//timer
	this->timer = Timer();
	if(!timer.Initialize(fps)) {
		std::cerr << __FUNCTION__ << ": Timer not initialized" << std::endl;
		return false;
	}
	this->barrelTimer  = b2Timer();

	//graphics device
	this->gDevice = gDevice;

	//inputdevice
	this->iDevice = iDevice;

	//aLibrary
	this->aLibrary = new ArtAssetLibrary;
	if(!aLibrary->initialize(gDevice)) {
		std::cerr << __FUNCTION__ << ": aLibrary not initialized" << std::endl;
		return false;
	}

	//Physics Asset Library
	this->pLibrary = new PhysicsAssetLibrary;
	if(!pLibrary->initialize()) {
		std::cerr << __FUNCTION__ << ": pLibrary not initialized" << std::endl;
		return false;
	}

	this->mLibrary = new MusicAssetLibrary;
	if(!mLibrary->initialize()) {
		std::cerr << __FUNCTION__ << ": mLibrary not initialized" << std::endl;
		return false;
	}

	this->view = new View;
	if(!view->initialize(iDevice, 0,0)) {
		std::cerr << __FUNCTION__ << " : cannot initialize view" << std::endl;
	}

	//C++11 mersenne twister
	std::random_device rd;
	randomGen = new std::mt19937(rd());

	//physics world
	b2Vec2 gravity(RW2PW(0), RW2PW(0));
	this->world = new b2World(gravity);

	//resource manager to manage Actors
	resourceManager = new ResourceManager();
	resourceManager->Initialize(this);

	//this->debugDraw = new Box2DDebugDraw();
	//debugDraw->Initialize(gDevice);
	//debugDraw->SetFlags(b2Draw::e_shapeBit | b2Draw::e_aabbBit);
	//world->SetDebugDraw(debugDraw);
	world->SetDebugDraw(NULL);
	MyContactListener* contactListener = new MyContactListener();
	world->SetContactListener(contactListener);

	return true;
}


bool Game::loadLevel(std::string configFile) {
	TiXmlDocument doc(configFile.c_str());
	doc.LoadFile();
	TiXmlElement* root = nullptr;
	root = doc.FirstChildElement("Level");
	if(!root) {
		std::cerr << __FUNCTION__ << " : cannot load " << configFile << std::endl;
		return false;
	}
	for(TiXmlElement* node = root->FirstChildElement("GameAsset"); node; node = node->NextSiblingElement("GameAsset")) {
		ActorInfo info; 
		info.name = node->Attribute("name");
		node->QueryFloatAttribute("x", &info.x);
		node->QueryFloatAttribute("y", &info.y);
		node->QueryFloatAttribute("angle", &info.angle);
		resourceManager->MarkForCreation(info);
	}
	this->leftBank = new std::vector<b2Vec2>();
	for(TiXmlElement* node = root->FirstChildElement("LeftPoint"); node; node = node->NextSiblingElement("LeftPoint")) {
		b2Vec2 point;
		node->QueryFloatAttribute("x", &point.x);
		node->QueryFloatAttribute("y", &point.y);
		point.x = RW2PW(point.x); //banks are in physic world!!
		point.y = RW2PW(point.y);
		leftBank->push_back(point);
	}

	this->rightBank = new std::vector<b2Vec2>();
	for(TiXmlElement* node = root->FirstChildElement("RightPoint"); node; node = node->NextSiblingElement("RightPoint")) {
		b2Vec2 point;
		node->QueryFloatAttribute("x", &point.x);
		node->QueryFloatAttribute("y", &point.y);
		point.x = RW2PW(point.x); //banks are in physic world!!
		point.y = RW2PW(point.y);
		rightBank->push_back(point);
	}

	//Add player
	ActorInfo info;
	info.name = "Player";
	info.x = 0; info.y = 0; info.angle =0;
	resourceManager->MarkForCreation(info);

	//build level from banks
	b2BodyDef bd;
	b2Body* edge = world->CreateBody(&bd);
	b2EdgeShape shape;

	//build top and bottom boundaries
	//shape.Set(leftBank->front(), rightBank->front());
	//edge->CreateFixture(&shape,0);

	//shape.Set(leftBank->back(), rightBank->back());
	//edge->CreateFixture(&shape,0);

	for(auto i = leftBank->begin();(i + 1) != leftBank->end(); i++) {
		shape.Set(*i, *(i+1));
		edge->CreateFixture(&shape,0);
	}
	for(auto i = rightBank->begin();(i + 1) != rightBank->end(); i++) {
		shape.Set(*i, *(i+1));
		edge->CreateFixture(&shape,0);
	}
	return true;
}


void Game::run() {
	timer.start();//get time of start of frame

	update(); //update objects
	world->Step(dt, 8,3); //update world
	gDevice->Begin(); //clear screen
	gDevice->Draw(std::to_string(score),leftBank, rightBank); //get each object's coords and tell the renderer
	//world->DrawDebugData();
	gDevice->Present(); //push pixels
	timer.fpsRegulate(); //wait until enough time has passed to start the next frame
}

void Game::update() {
	//spawn new barrels at top of screen
	if(barrelTimer.GetMilliseconds() > 1000) {
		ActorInfo ai;
		ai.name = "Barrel";
		ai.angle = 0;
		//only want to spawn from the top between the banks
		std::uniform_real_distribution<GAME_FLT>dist(PW2RW(leftBank->front().x+1), PW2RW(rightBank->front().x-1));
		ai.x = dist(*randomGen);
		ai.y = 10;
		resourceManager->MarkForCreation(ai);
		barrelTimer.Reset();
	}
	resourceManager->AddToActors();
	resourceManager->UpdateActors();
	resourceManager->RemoveFromActors();
}

bool Game::destroy() {
	delete resourceManager;
	aLibrary->destroy();
	delete aLibrary;
	delete pLibrary;
	mLibrary->destroy();
	delete mLibrary;
	delete view;
	delete randomGen;
	delete world;
	//delete debugDraw;
	return true;
}

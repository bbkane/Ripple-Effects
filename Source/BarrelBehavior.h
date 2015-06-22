#ifndef INFANTRY_BEHAVIOR_H
#define INFANTRY_BEHAVIOR_H

#include"Component.h"
#include <random>

class Actor;
class GraphicsDevice;
class Texture;
class MusicAssetLibrary;

class BarrelBehavior : public Component
{
public:
	BarrelBehavior(std::shared_ptr<Actor>);
	~BarrelBehavior();
	void Initialize(std::vector<b2Vec2>* leftBank, std::vector<b2Vec2>* rightbank,MusicAssetLibrary*,GAME_INT * score,float dt);
	void Start();
	void Update();
	void Finish();
	void StartTouchingDock();
	void StartTouchingRock();
protected:
	MusicAssetLibrary* mLibrary;
	float dt;
	float angularSpeed;
	std::vector<b2Vec2> * leftBank;
	std::vector<b2Vec2> * rightBank;
	b2Timer timeLived;
	int touchingDock;
	int touchingRock;
	GAME_INT * score;
};


#endif
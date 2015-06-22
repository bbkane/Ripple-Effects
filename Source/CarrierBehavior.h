#ifndef CARRIER_BEHAVIOR_H
#define CARRIER_BEHAVIOR_H

#include"Component.h"
#include <random>
class Actor;
class GraphicsDevice;
class Texture;

class CarrierBehavior : public Component
{
public:
	CarrierBehavior(std::shared_ptr<Actor>);
	~CarrierBehavior();
	void Initialize(std::mt19937*, float);
	void Start();
	void Update();
	void Finish();

protected:
	float dt;
	GAME_FLT turnTightness;
};


#endif
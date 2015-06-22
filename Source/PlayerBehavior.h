#ifndef PLAYER_BEHAVIOR_H
#define PLAYER_BEHAVIOR_H

#include"Component.h"
class Actor;
class GraphicsDevice;
class Texture;
class InputDevice;
class ResourceManager;

class PlayerBehavior : public Component
{
public:
	PlayerBehavior(std::shared_ptr<Actor>);
	~PlayerBehavior();
	void Initialize(ResourceManager*,InputDevice *, float);
	void Start();
	void Update();
	void Finish();

protected:
	float dt;
	InputDevice* iDevice;
	ResourceManager* resourceManager;
	b2Timer timer;
};


#endif
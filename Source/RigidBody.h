#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include"Component.h"
#include "Box2D/Box2D.h"
#include "Texture.h"
#include "PhysicsAssetLibrary.h"
#include "Definitions.h"

class RigidBody : public Component
{
public:

	RigidBody(std::shared_ptr<Actor>);
	~RigidBody();
	void Initialize(b2World* world,Texture* texture, GamePhysics gamePhysics,std::string name, float x, float y, float angle);

	void Start();
	void Update();
	void Finish();
	b2Vec2 GetPosition();
	float GetAngle();
	GAME_FLT GetAngularForce();
	GAME_FLT GetLinearForce();

	b2Body* GetBody();
protected:
	
    b2Body* body;
	GAME_FLT angularForce;
	GAME_FLT linearForce;
};


#endif
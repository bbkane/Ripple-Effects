#include"Definitions.h"
#include"RigidBody.h"

#include <iostream>

RigidBody::RigidBody(std::shared_ptr<Actor> owner) : Component(owner){}

RigidBody::~RigidBody(){}


//should make this return a value so I can check for errors!
void RigidBody::Initialize(b2World* world, Texture* texture, GamePhysics gamePhysics,std::string name, float x, float y, float angle)
{

	b2BodyDef bd;

	if(gamePhysics.type == "dynamic") {
		bd.type = b2_dynamicBody;
	} else if(gamePhysics.type == "static") {
		bd.type = b2_staticBody;
	}

	//Intialize Body Definition
	bd.position.Set(RW2PW(x),RW2PW(y));
    bd.angle = RW2PWAngle(angle);
	//bd.userData = this;


	//Create Body within Physics World
	body = world->CreateBody(&bd);

	b2PolygonShape polyShape;
	polyShape.SetAsBox(RW2PW((float)texture->getWidth()/2.0f), RW2PW((float)texture->getHeight()/2.0f));

	b2CircleShape circleShape;
	circleShape.m_radius = RW2PW((float)texture->getWidth()/2.0f);

	b2FixtureDef fixtureDef;
	if(gamePhysics.shape == "rectangle") {
		fixtureDef.shape = &polyShape;
	} else {
		fixtureDef.shape = &circleShape;
	}

	body->SetAngularDamping(gamePhysics.angularDamping);
	body->SetLinearDamping(gamePhysics.linearDamping);

	this->linearForce = gamePhysics.linearForce;
	this->angularForce = gamePhysics.angularForce;

	fixtureDef.density = gamePhysics.density;
	fixtureDef.friction = gamePhysics.friction;
	fixtureDef.restitution = gamePhysics.restitution;

	body->SetUserData(_owner.get()); //hopefully this works

	//Create Fixture within Body (links to Physics World)
	body->CreateFixture(&fixtureDef);
}

void RigidBody::Start(){}

void RigidBody::Update()
{
	if(body->GetPosition().x > RW2PW((int)SCREEN_WIDTH) || body->GetPosition().x < RW2PW(0)) {
		_owner->SetIsAlive(false);
}
	if(body->GetPosition().y > RW2PW((int)SCREEN_HEIGHT) || body->GetPosition().y < RW2PW(0)) {
		_owner->SetIsAlive(false);
	}
}

void RigidBody::Finish(){}


b2Vec2 RigidBody::GetPosition(){
	return(body->GetPosition());
}

float RigidBody::GetAngle()
{
	return(body->GetAngle());
}

b2Body* RigidBody::GetBody()
{
	return(body);
}

GAME_FLT RigidBody::GetLinearForce()
{
	return linearForce;
}

GAME_FLT RigidBody::GetAngularForce()
{
	return angularForce;
}
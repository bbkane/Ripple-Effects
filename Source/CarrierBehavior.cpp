#include"Definitions.h"
#include"CarrierBehavior.h"
#include"RigidBody.h"
#include <cmath>

//this class isn't needed, but it's note hurting anything either. I'm going to leave it. What if "Ripple Effects" needs carriers?
CarrierBehavior::CarrierBehavior(std::shared_ptr<Actor> owner) : Component(owner){}

CarrierBehavior::~CarrierBehavior(){}

void CarrierBehavior::Initialize(std::mt19937* randomGen, float dt)
{
	this->dt = dt;
	GAME_FLT maxTurnTightness = 0.05;
	std::uniform_real_distribution<GAME_FLT> dist(-maxTurnTightness, maxTurnTightness);
	this->turnTightness = dist(*(randomGen));
}

void CarrierBehavior::Start(){}

void CarrierBehavior::Update()
{
	//Convert Physics World Position to Render World Position
	std::shared_ptr<RigidBody> rigidBody = _owner->GetComponent<RigidBody>();
	b2Body* body = rigidBody->GetBody();

	if(body)
	{
		b2Vec2 forceVec = b2Vec2(cos((body->GetAngle() - b2_pi/2)) * rigidBody->GetLinearForce(),
			sin((body->GetAngle() - b2_pi/2)) * rigidBody->GetLinearForce());
		body->SetTransform(forceVec + body->GetPosition(), body->GetAngle() + turnTightness);
	}
}

void CarrierBehavior::Finish(){}

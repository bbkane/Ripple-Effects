#include "RipplePhysics.h"
#include <iostream>
#include "RippleGFX.h"

//this depends on graphics!! put that in first!!!

RipplePhysics::RipplePhysics(std::shared_ptr<Actor> owner) : Component(owner){}

RipplePhysics::~RipplePhysics(){}

//should make this return a value so I can check for errors!
void RipplePhysics::Initialize(b2World* world)
{
	this->world = world;
	this->queryCallback = MyQueryCallback();
	
	this->blastPower = 3;

}

void RipplePhysics::Start(){}

void RipplePhysics::Update()
{
	//code blatantly stolen from http://www.iforce2d.net/b2dtut/explosions

	b2Vec2 center;
	center.x = RW2PW(_owner->GetComponent<RippleGFX>()->GetX());

	center.y = RW2PW(_owner->GetComponent<RippleGFX>()->GetY());
	this->blastRadius = RW2PW(_owner->GetComponent<RippleGFX>()->GetR());
	b2AABB aabb;
	aabb.lowerBound = center - b2Vec2(blastRadius, blastRadius);
	aabb.upperBound = center + b2Vec2(blastRadius, blastRadius);
	world->QueryAABB(&queryCallback, aabb);
	for(unsigned int i = 0; i < queryCallback.foundBodies.size(); i++) {
		b2Body * body = queryCallback.foundBodies[i];
		b2Vec2 bodyCom = body->GetWorldCenter();
		if( (bodyCom - center).Length() >= blastRadius)
			continue;
		ApplyBlastImpulse(body, center, bodyCom, blastPower);
	}
	if( _owner->GetComponent<RippleGFX>()->lifeTime.GetMilliseconds() > 200) {
		_owner->SetIsAlive(false);
	}
}

void RipplePhysics::Finish(){}

void RipplePhysics::ApplyBlastImpulse(b2Body* body, b2Vec2 blastCenter, b2Vec2 applyPoint, float blastPower)
    {
		//code blatantly stolen from http://www.iforce2d.net/b2dtut/explosions

        //ignore the grenade itself, and any non-dynamic bodies
        if (body->GetType() != b2_dynamicBody )
            return;
        b2Vec2 blastDir = applyPoint - blastCenter;
        float distance = blastDir.Normalize();
        //ignore bodies exactly at the blast point - blast direction is undefined
        if ( distance == 0 )
            return;
        float invDistance = 1 / distance;
        float impulseMag = blastPower * invDistance * invDistance;
        impulseMag = b2Min( impulseMag, 500.0f );
        body->ApplyLinearImpulse( impulseMag * blastDir, applyPoint, true);
    }

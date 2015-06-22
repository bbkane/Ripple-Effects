#ifndef RIPPLE_PHYSICS
#define RIPPLE_PHYSICS

#include"Component.h"
#include "Box2D/Box2D.h"
#include "Definitions.h"
#include <vector>

class RippleGFX;

//subclass b2QueryCallback for proximity query callback
class MyQueryCallback : public b2QueryCallback {
public:
    std::vector<b2Body*> foundBodies;

    bool ReportFixture(b2Fixture* fixture) {
        foundBodies.push_back( fixture->GetBody() );
        return true;//keep going to find all fixtures in the query area
    }
};

class RipplePhysics : public Component
{
public:

	RipplePhysics(std::shared_ptr<Actor>);
	~RipplePhysics();
	void Initialize(b2World* world);

	void Start();
	void Update();
	void Finish();

	void ApplyBlastImpulse(b2Body* body, b2Vec2 blastCenter, b2Vec2 applyPoint, float blastPower);
protected:
	MyQueryCallback queryCallback;
	b2World * world;
	float blastRadius;
	float blastPower;
};


#endif
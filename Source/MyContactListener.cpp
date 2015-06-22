#include "MyContactListener.h"
#include "Definitions.h"
#include "Actor.h"
#include "BarrelBehavior.h"
void MyContactListener::BeginContact(b2Contact* contact) 
{
	//Thank you Sean
	Actor* actorA = static_cast<Actor*>( contact -> GetFixtureA() -> GetBody() -> GetUserData());
	Actor* actorB = static_cast<Actor*>( contact -> GetFixtureB() -> GetBody() -> GetUserData());
	//If they both are actors and not walls
	if(actorA && actorB) {
		if(actorA->GetName() == "Barrel") {
			if(actorB->GetName() == "Rock") {
				actorA->GetComponent<BarrelBehavior>()->StartTouchingRock();
			} else if(actorB->GetName() == "Dock") {
				actorA->GetComponent<BarrelBehavior>()->StartTouchingDock();
			}
		}
		if(actorB->GetName() == "Barrel") {
			if(actorA->GetName() == "Rock") {
				actorB->GetComponent<BarrelBehavior>()->StartTouchingRock();
			} else if(actorA->GetName() == "Dock") {
				actorB->GetComponent<BarrelBehavior>()->StartTouchingDock();
			}
		}
	}
}

void MyContactListener::EndContact(b2Contact* contact) {}

void MyContactListener::PreSolve(b2Contact* contact,const b2Manifold* oldManifold) {}

void MyContactListener::PostSolve(b2Contact* contact,const b2ContactImpulse* impulse){}
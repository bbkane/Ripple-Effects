#ifndef MY_CONTACT_LISTENER
#define MY_CONTACT_LISTENER
#include <Box2D\Box2D.h>

class MyContactListener: public b2ContactListener
{
public: 
    virtual void BeginContact(b2Contact* contact) override;
    virtual void EndContact(b2Contact* contact) override;
    virtual void PreSolve(b2Contact* contact, const b2Manifold* oldManifold) override;    
    virtual void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) override;
 
};
#endif
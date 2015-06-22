#include "Actor.h"
#include "Component.h"

Component::Component(std::shared_ptr<Actor> owner) : _owner(owner){}

Component::~Component(){}

void Component::OwnerDestroyed()
{
	Finish();
	_owner = NULL;
}

std::shared_ptr<Actor> Component::GetOwner()
{
	return(_owner);
}
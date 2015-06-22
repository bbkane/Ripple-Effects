#ifndef COMPONENT_H
#define COMPONENT_H

#include <memory>
#include "Actor.h"

class Component
{
public:
	Component(std::shared_ptr<Actor> owner);
	~Component();
	void OwnerDestroyed();
	std::shared_ptr<Actor> GetOwner();
	virtual void Start()=0;
	virtual void Update()=0;
	virtual void Finish()=0;

protected:
	std::shared_ptr<Actor> _owner;
};

#endif
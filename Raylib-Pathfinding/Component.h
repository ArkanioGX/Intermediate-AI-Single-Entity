#pragma once
#include "Actor.h"

class Component
{
public:
	Actor* getOwner();

	virtual void update(float dt);

private:
	Actor* owner;
};


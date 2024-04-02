#include "Actor.h"

#include "Game.h"

Actor::Actor()
{
	Game::instance().addActor(this);
}

void Actor::update(float dt)
{
	for (int i = 0; i < Components.size(); i++) {
		Components[i]->update(dt);
	}
}

bool Actor::addComponent(Component* c)
{
	Components.push_back(c);
	return true;
}

Game* Actor::getGame()
{
	return nullptr;
	//return Game::game ;
}

Vector2 Actor::getPosition()
{
	return pos;
}

Vector2 Actor::getScale()
{
	return scale;
}

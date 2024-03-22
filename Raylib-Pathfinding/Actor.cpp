#include "Actor.h"
#include "Component.h"
#include "Game.h"

Actor::Actor()
{

}

void Actor::update(float dt)
{
	for (int i = 0; i < Components.size(); i++) {
		Components[i]->update(dt);
	}
}

Game* Actor::getGame()
{
	return nullptr;
	//return Game::game ;
}

#include "Game.h"



Game::Game()
{
	//game = this;
}

void Game::initialize()
{
	
}

void Game::loop()
{
	float dt = 1 / 60;
	for (int i = 0; i < actorsList.size(); i++) {
		actorsList[i]->update(dt);
	}
}

void Game::draw()
{
}

void Game::close()
{
}

void Game::addActor(Actor* a)
{
	actorsList.push_back(a);
}

void Game::removeActor(Actor* a)
{
}

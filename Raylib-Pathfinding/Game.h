#pragma once
#include "Actor.h"

class Game
{
	std::vector<Actor*> actorsList;
public:
	Game();

	void initialize();
	void loop();
	void draw();
	void close();

	void addActor(Actor*);
	void removeActor(Actor*);

	//static Game* game;
};


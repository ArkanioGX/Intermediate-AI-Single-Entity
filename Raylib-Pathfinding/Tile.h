#pragma once
#include "raylib.h"


class Tile {
public:

	Tile(float f, Color c = DARKGREEN); 


	float pathToughness = 1;
	Color tileColor;

	static const Tile Ground;
	static const Tile Wall;
	static const Tile Water;
	static const Tile Bridge;
};


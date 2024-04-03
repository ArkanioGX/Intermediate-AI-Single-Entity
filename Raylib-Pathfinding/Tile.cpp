#include "Tile.h"
#include <limits>
#define inf std::numeric_limits<float>::max()

Tile::Tile(float f, Color c):
	pathToughness(f),
	tileColor(c)
{

}

const Tile Tile::Ground(1, DARKGREEN);
const Tile Tile::Wall(inf, GRAY);
const Tile Tile::Water(10, BLUE);
const Tile Tile::Bridge(3, DARKBROWN);


#pragma once
#include "Component.h"
#include <vector>
#include "Tile.h"
class TilemapComponent : public Component
{
private:
	std::vector<std::vector<Tile>> tilemap = {
		{Tile::Ground,	Tile::Ground,	Tile::Ground,	Tile::Ground,	Tile::Ground,	Tile::Ground,	Tile::Wall,		Tile::Wall},
		{Tile::Wall,	Tile::Wall,		Tile::Water,	Tile::Water,	Tile::Bridge,	Tile::Water,	Tile::Water,	Tile::Wall},
		{Tile::Wall,	Tile::Ground,	Tile::Ground,	Tile::Ground,	Tile::Ground,	Tile::Ground,	Tile::Water,	Tile::Water},
		{Tile::Ground,	Tile::Ground,	Tile::Ground,	Tile::Ground,	Tile::Ground,	Tile::Ground,	Tile::Ground,	Tile::Water},
		{Tile::Ground,	Tile::Wall,		Tile::Ground,	Tile::Wall,		Tile::Wall,		Tile::Wall,		Tile::Wall,		Tile::Wall},
		{Tile::Ground,	Tile::Wall,		Tile::Ground,	Tile::Ground,	Tile::Ground,	Tile::Ground,	Tile::Ground,	Tile::Ground},
		{Tile::Water,	Tile::Wall,		Tile::Wall,		Tile::Wall,		Tile::Wall,		Tile::Wall,		Tile::Wall,		Tile::Ground},
		{Tile::Water,	Tile::Water,	Tile::Ground,	Tile::Ground,	Tile::Ground,	Tile::Ground,	Tile::Ground,	Tile::Ground}
	};

public:

	TilemapComponent(class Actor* ownerP);

	void update(float dt) override;

	size_t getMapSize();

	Tile* getTileAt(int x, int y);
};


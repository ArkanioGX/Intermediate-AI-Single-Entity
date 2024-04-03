#include "TilemapComponent.h"

TilemapComponent::TilemapComponent(Actor* ownerP) :
	Component(ownerP)
{
}

void TilemapComponent::update(float dt)
{
}

size_t TilemapComponent::getMapSize()
{
	return tilemap.size();
}

Tile* TilemapComponent::getTileAt(int x, int y)
{
	return &tilemap[x][y];
}

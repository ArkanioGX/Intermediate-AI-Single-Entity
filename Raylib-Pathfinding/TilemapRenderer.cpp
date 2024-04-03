#include "TilemapRenderer.h"
#include "TilemapComponent.h"
#include "Actor.h"
#include <iostream>

TilemapRenderer::TilemapRenderer(Actor* owner):
	RenderComponent(owner)
{
}

void TilemapRenderer::draw()
{
	TilemapComponent* tmc = getOwner()->getComponent<TilemapComponent*>();
	Vector2 pos = getOwner()->getPosition();
	Vector2 scale = getOwner()->getScale();

	size_t mapSize = tmc->getMapSize();

	for (int x = 0; x < mapSize; x++) {
		for (int y = 0; y < mapSize; y++) {
			float xPos = pos.x + x * scale.x;
			float yPos = pos.y + y * scale.y;

			DrawRectangle(xPos, yPos, scale.x, scale.y, tmc->getTileAt(y, x)->tileColor);
		}
	}
	//std::cout << tmc->f;
}

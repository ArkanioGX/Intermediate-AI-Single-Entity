#include "PathfindingComponent.h"
#include "Actor.h"
#include "TilemapComponent.h"
//#include "raylib.h"





PathfindingComponent::PathfindingComponent(Actor* ownerP):
	RenderComponent(ownerP)
{
	findPath();
}

void PathfindingComponent::update(float dt)
{
}

void PathfindingComponent::draw()
{
	Vector2 actPos = getOwner()->getPosition();
	Vector2 actScale = getOwner()->getScale();
	//Start Pos Draw
	float startPosX = actPos.x + start.x * actScale.x + (actScale.x/2);
	float startPosY = actPos.y + start.y * actScale.y + (actScale.y / 2);
	DrawCircle(startPosX, startPosY, 25, GOLD);

	//End Pos Draw
	float endPosX = actPos.x + end.x * actScale.x + (actScale.x / 2);
	float endPosY = actPos.y + end.y * actScale.y + (actScale.y / 2);
	DrawCircle(endPosX, endPosY, 25, RED);

	//Path render
	if (!finalPath.empty()) {
		for (int i = 0; i < finalPath.size() - 1; i++) {
			Vector2 startLine = finalPath[i];
			float lStartPosX = actPos.x + startLine.x * actScale.x + (actScale.x / 2);
			float lStartPosY = actPos.y + startLine.y * actScale.y + (actScale.y / 2);
			startLine = { lStartPosX,lStartPosY };

			Vector2 endLine = finalPath[i+1];
			lStartPosX = actPos.x + endLine.x * actScale.x + (actScale.x / 2);
			lStartPosY = actPos.y + endLine.y * actScale.y + (actScale.y / 2);
			endLine = { lStartPosX,lStartPosY };

			DrawLineEx(startLine, endLine, 10, GOLD);
		}

		for (int i = 1; i < finalPath.size() - 1; i++) {
			Vector2 betweenLine = finalPath[i];
			float lPosX = actPos.x + betweenLine.x * actScale.x + (actScale.x / 2);
			float lPosY = actPos.y + betweenLine.y * actScale.y + (actScale.y / 2);
			betweenLine = { lPosX,lPosY };

			DrawCircle(betweenLine.x,betweenLine.y, 10, GOLD);
		}

	}
}

void PathfindingComponent::findPath()
{
	std::vector<Node*> openList = std::vector<Node*>();
	std::vector<Node*> closedList = std::vector<Node*>();

	initNodeMap();

}

void PathfindingComponent::initNodeMap() {
	

	TilemapComponent* tmc = getOwner()->getComponent<TilemapComponent*>();

	nodeMap.resize(tmc->getMapSize(), std::vector<Node*>(tmc->getMapSize()));

	for (int y = 0; y < tmc->getMapSize(); y++) {
		for (int x = 0; x < tmc->getMapSize(); x++) {
			Node* n = new Node();
			n->x = x;
			n->y = y;
			n->g = 0;
			n->h = 0;
			n->f = n->g + n->h;
			n->Parent = nullptr;

			n->toughness = tmc->getTileAt(x,y)->pathToughness;
			nodeMap[x][y] = n;
		}
	}
	return;
}

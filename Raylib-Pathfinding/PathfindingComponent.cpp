#include "PathfindingComponent.h"
#include "Actor.h"
#include "TilemapComponent.h"
#include <iostream>
#define inf std::numeric_limits<float>::max()
//#include "raylib.h"





PathfindingComponent::PathfindingComponent(Actor* ownerP):
	RenderComponent(ownerP)
{
	findPath();
}

void PathfindingComponent::update(float dt)
{
	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
		Vector2 mpos = GetMousePosition();

		TilemapComponent* tmc = getOwner()->getComponent<TilemapComponent*>();
		int x = mpos.y / GetRenderWidth() * tmc->getMapSize();
		int y = mpos.x / GetRenderHeight() * tmc->getMapSize();
		Vector2 tPos = { float(x),float(y) };
		if (checkTileIfFree(tPos)) {
			start = Vector2{ float(x),float(y) };
			findPath();
		}
	}
	else if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
		Vector2 mpos = GetMousePosition();

		TilemapComponent* tmc = getOwner()->getComponent<TilemapComponent*>();
		int x = mpos.y / GetRenderWidth() * tmc->getMapSize();
		int y = mpos.x / GetRenderHeight() * tmc->getMapSize();
		Vector2 tPos = { float(x),float(y) };
		if (checkTileIfFree(tPos)) {
			end = Vector2{ float(x),float(y) };
			findPath();
		}
	}
	
}

void PathfindingComponent::draw()
{
	Vector2 actPos = getOwner()->getPosition();
	Vector2 actScale = getOwner()->getScale();
	
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

		for (int i = 1; i < finalPath.size(); i++) {
			Vector2 betweenLine = finalPath[i];
			float lPosX = actPos.x + betweenLine.x * actScale.x + (actScale.x / 2);
			float lPosY = actPos.y + betweenLine.y * actScale.y + (actScale.y / 2);
			betweenLine = { lPosX,lPosY };

			DrawCircle(betweenLine.x,betweenLine.y, 10, GOLD);
		}

	}

	//Start Pos Draw
	float startPosX = actPos.x + start.x * actScale.x + (actScale.x / 2);
	float startPosY = actPos.y + start.y * actScale.y + (actScale.y / 2);
	DrawCircle(startPosY, startPosX, 25, GOLD);

	//End Pos Draw
	float endPosX = actPos.x + end.x * actScale.x + (actScale.x / 2);
	float endPosY = actPos.y + end.y * actScale.y + (actScale.y / 2);
	DrawCircle(endPosY, endPosX, 25, RED);
}

void PathfindingComponent::findPath()
{
	finalPath.clear();

	std::vector<Node*> openList = std::vector<Node*>();
	std::vector<Node*> closedList = std::vector<Node*>();

	initNodeMap();
	Node* startNode = nodeMap[start.x][start.y];
	startNode->f = 0;
	Node* endNode = nodeMap[end.x][end.y];

	openList.push_back(startNode);

	while (!openList.empty()) {
		Node* currentNode;
		currentNode = searchMin(openList);
		openList.erase(openList.begin() + getIndexFromValue(openList, currentNode));
		closedList.push_back(currentNode);

		if (currentNode == endNode) {
			std::cout << "GGs you won" << std::endl;
			Node* n = endNode;
			while (n != startNode) {
				finalPath.push_back(Vector2{float(n->y),float(n->x)});
				n = n->Parent;
			}
			finalPath.push_back(Vector2{ float(n->y),float(n->x) });
			return;
		}
		std::vector<Node*> childNodes = setChildren(currentNode,closedList);
		for (int i = 0; i < childNodes.size(); i++) {
			Node* childNode = childNodes[i];
			if (ifIsInList(childNode, closedList)) {
				continue;
			}
			childNode->g = currentNode->g + getDist(currentNode, childNode) * childNode->toughness;
			childNode->h = getDist(childNode, endNode);
			childNode->f = childNode->g + childNode->h;

			int listPos = ifIsInListViaPos(childNode, openList);
			if (listPos != -1) {
				if (openList[listPos]->g < childNode->g) {
					continue;
				}
			}
			openList.push_back(childNode);
		}
	}
}

float PathfindingComponent::getDist(Node* n1, Node* n2) {
	return sqrt(pow((n1->x - n2->x), 2) + pow((n1->y - n2->y), 2));
}

int PathfindingComponent::getIndexFromValue(std::vector<Node*>& list, Node* v) {
	for (int i = 0; i < list.size(); i++) {
		if (list[i] == v) {
			return  i;
		}
	}
	return 0;
}

Node* PathfindingComponent::searchMin(std::vector<Node*>& list) {
	int fMin = 0;

	for (int j = 0; j < list.size(); j++) {
		if (list[j]->f < list[fMin]->f)
		{
			fMin = j;
		}
	}
	return list[fMin];
}

std::vector<Node*> PathfindingComponent::setChildren(Node* n, std::vector<Node*>& cList) {
	std::vector<Node*> children = std::vector<Node*>();
	for (int x = -1; x < 2; x++) {
		if ((n->x + x >= 0) && (n->x + x < nodeMap[0].size())) {
			for (int y = -1; y < 2; y++) {
				if ((n->y + y >= 0) && (n->y + y < nodeMap[0].size())) {
					int xP = n->x + x;
					int yP = n->y + y;
					if (!(x == 0 && y == 0) && nodeMap[xP][yP]->toughness != inf ) 
					{
						if (!ifIsInList(nodeMap[xP][yP], cList)) {
							nodeMap[xP][yP]->Parent = n;
							children.push_back(nodeMap[xP][yP]);
						}
					}
				}
			}
		}
	}
	return children;
}

bool PathfindingComponent::ifIsInList(Node* value, std::vector<Node*> list) {
	for (int i = 0; i < list.size(); i++) {
		if (hasSamePos(list[i], value)) {
			return true;
		}
	}
	return false;
}

int PathfindingComponent::ifIsInListViaPos(Node* value, std::vector<Node*> list) {
	for (int i = 0; i < list.size(); i++) {
		if (hasSamePos(list[i], value)) {
			return i;
		}
	}
	return -1;
}

bool PathfindingComponent::hasSamePos(Node* n1, Node* n2)
{
	return n1->x == n2->x && n1->y == n2->y;
}

bool PathfindingComponent::hasSamePos(Vector2 p1,Vector2 p2)
{
	return p1.x == p2.x && p1.y == p2.y;
}

bool PathfindingComponent::checkTileIfFree(Vector2 pos)
{
	TilemapComponent* tmc = getOwner()->getComponent<TilemapComponent*>();
	return ((!hasSamePos(pos, start) && !hasSamePos(pos, end)) && tmc->getTileAt(pos.x, pos.y)->pathToughness != inf);
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

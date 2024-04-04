#pragma once
#include "RenderComponent.h"
#include "raylib.h"
#include <limits>
#include <vector>

struct Node {
public:
	float g, h, f;
	Node* Parent;
	int x, y;
	float toughness;
};

class PathfindingComponent : public RenderComponent
{
	std::vector<Node*> openList;
	std::vector<Node*> closedList;

	Vector2 start = {0,0};
	Vector2 end = { 7,2 };

	std::vector<Vector2> finalPath = std::vector<Vector2>();

	std::vector<std::vector<Node*>> nodeMap;

public:
	PathfindingComponent(class Actor* ownerP);

	void update(float dt) override;

	void draw() override;

	void findPath();

	void initNodeMap();

	float getDist(Node* n1, Node* n2);

	int getIndexFromValue(std::vector<Node*>& list, Node* v);

	Node* searchMin(std::vector<Node*>& list);

	std::vector<Node*> setChildren(Node* n, std::vector<Node*>& cList);

	bool ifIsInList(Node* value, std::vector<Node*> list);

	int ifIsInListViaPos(Node* value, std::vector<Node*> list);

	bool hasSamePos(Node* n1, Node* n2);
	bool hasSamePos(Vector2 p1, Vector2 p2);

	bool checkTileIfFree(Vector2 pos);
};




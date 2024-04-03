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
	

	Vector2 start = {0,0};
	Vector2 end = { 7,7 };

	std::vector<Vector2> finalPath = std::vector<Vector2>();

	std::vector<std::vector<Node*>> nodeMap;

public:
	PathfindingComponent(class Actor* ownerP);

	void update(float dt) override;

	void draw() override;

	void findPath();

	void initNodeMap();
};




#pragma once
#include <vector>
#include "Component.h"
#include "raylib.h"

class Actor
{
private:
	std::vector<Component*> Components;

	Vector2 pos = Vector2{ 0,0 };
	Vector2 scale = Vector2{ 100,100 };

public:
	Actor();

	void update(float dt);
	bool addComponent(Component*);
	bool removeComponent(Component*);

	template <typename CompType>
	inline Component* getComponent() {
		Component* res = nullptr;
		for (int i = 0; i < Components.size(); i++) {
			res = dynamic_cast<CompType*>(Components[i]);
			if (res) { break; }
		}
		return res;
	}

	class Game* getGame();

	Vector2 getPosition();
	Vector2 getScale();
};

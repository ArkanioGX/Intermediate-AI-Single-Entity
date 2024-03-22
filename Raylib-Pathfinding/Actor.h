#pragma once
#include <vector>

class Actor
{
private:
	std::vector<class Component*> Components;

public:
	Actor();

	void update(float dt);
	bool addComponent(class Component*);
	bool removeComponent(class Component*);

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
};

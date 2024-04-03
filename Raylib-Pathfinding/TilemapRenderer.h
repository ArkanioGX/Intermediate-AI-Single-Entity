#pragma once
#include "RenderComponent.h"

class TilemapRenderer : public RenderComponent
{
public:
	TilemapRenderer(class Actor* owner);

	void draw() override;
};


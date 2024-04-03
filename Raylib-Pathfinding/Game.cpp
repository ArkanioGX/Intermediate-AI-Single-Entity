#include "Game.h"
#include "raylib.h"
#include "TilemapRenderer.h"
#include "TilemapComponent.h"
#include "PathfindingComponent.h"



Game::Game()
{
}

void Game::load()
{
	Actor* act = new Actor();
	TilemapComponent* tmc = new TilemapComponent(act);
	TilemapRenderer* rc = new TilemapRenderer(act);
	PathfindingComponent* pfc = new PathfindingComponent(act);
}

void Game::loop()
{
	float dt = 1 / 60;
	for (int i = 0; i < actorsList.size(); i++) {
		actorsList[i]->update(dt);
	}
}

void Game::draw()
{
	BeginDrawing();
	ClearBackground(Color{ 255,255,255,255 });
	for (int i = 0; i < renderComponentList.size(); i++) {
		renderComponentList[i]->draw();
	}
	EndDrawing();
}

void Game::close()
{
}

void Game::addActor(Actor* a)
{
	actorsList.push_back(a);
}

void Game::removeActor(Actor* a)
{
	for (int i = 0; i < actorsList.size(); i++) {
		if (actorsList[i] == a) {
			actorsList.erase(actorsList.begin() + i);
			return;
		}
	}
}

void Game::addRenderComponent(RenderComponent* rc)
{
	renderComponentList.push_back(rc);
}

void Game::removeRenderComponent(RenderComponent* rc)
{
	for (int i = 0; i < renderComponentList.size(); i++) {
		if (renderComponentList[i] == rc) {
			renderComponentList.erase(renderComponentList.begin() + i);
			return;
		}
	}
}

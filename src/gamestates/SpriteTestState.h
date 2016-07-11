#pragma once
#include <gamestates\GameState.h>
#include <renderer\QuadBuffer.h>
#include <vector>
#include <gen\MeshGen.h>
#include <gen\MeshGenCommand.h>
#include <gen\MeshGenGUI.h>
#include <imgui\IMGUI.h>

class SpriteTestState : public ds::GameState {

public:
	SpriteTestState(ds::Game* game);
	~SpriteTestState();
	void init();
	int update(float dt);
	void render();
	int onChar(int ascii);
	void activate();
private:
	ds::Scene2D* _scene;
	RID _material;
	ID _first;
};


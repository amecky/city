#pragma once
#include <gamestates\GameState.h>
#include <renderer\QuadBuffer.h>
#include <vector>
#include <gen\MeshGen.h>
#include <gen\MeshGenCommand.h>
#include <gen\MeshGenGUI.h>
#include <imgui\IMGUI.h>

class ActionTestState : public ds::GameState {

public:
	ActionTestState();
	~ActionTestState();
	void init();
	int update(float dt);
	void render();
	int onChar(int ascii);
	void activate();
private:
	void drawGUI();
	ds::FPSCamera* _camera;
	ds::Mesh* _mesh;
	ds::Scene* _scene;
	ds::OrthoCamera* _orthoCamera;
	int _offset;
	bool _switch;
	RID _material;
	ID _id;
};


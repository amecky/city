#pragma once
#include <gamestates\GameState.h>
#include <renderer\QuadBuffer.h>
#include <vector>
#include <gen\MeshGen.h>
#include <gen\MeshGenCommand.h>
#include <gen\MeshGenGUI.h>
#include <renderer\SkyBox.h>

struct House {

	int tiles[2][2][5];
	int colors[2][2];
	p2i pos;

	House() {
		for (int i = 0; i < 2; ++i) {
			for (int j = 0; j < 2; ++j) {
				for (int k = 0; k < 5; ++k) {
					tiles[i][j][k] = -1;
				}
			}
		}
		for (int i = 0; i < 2; ++i) {
			for (int j = 0; j < 2; ++j) {
				colors[i][j] = 0;
			}
		}
		pos = p2i(0, 0);
	}
};

class GeoTestState : public ds::GameState {

public:
	GeoTestState(ds::Game* game);
	~GeoTestState();
	void init();
	int update(float dt);
	void render();
private:
	void buildTower(const p2i& gridPos);
	void buildHouse(const p2i& gridPos);
	void buildHouse(const House& house);

	void buildGrass(const p2i& gridPos);
	void buildWall(ds::gen::MeshGen& gen,int face_idx);
	void buildStreet(const p2i& gridPos,int bits);
	void createTile(int index, int directions);
	void createWindow(const v3& center);
	void buildTerrain();
	void buildTestTerrain();
	void drawGUI();
	void createCoords();
	void createStreets();
	void createHandrail(float length, float griderSize, int segments, float height);
	void createGriderBox(ds::gen::MeshGen* gen,float dim, float griderSize);
	ds::gen::MeshGen gen;
	ds::FPSCamera* _camera;
	ds::MeshBuffer* _buffer;
	ds::Mesh* _mesh;
	ds::Array<ds::Mesh*> _objects;
	ds::Scene* _scene;
	ds::OrthoCamera* _orthoCamera;
	ds::gen::CommandContext _ctx;
	ds::gen::MeshGenGUI* _gui;
	const char* _name;
	bool _pressed;
	ds::Array<ID> _ids;
	//ds::SkyBox* _skyBox;
	RID _material;
};


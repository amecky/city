#include "GeoTestState.h"
#include <utils\Log.h>
#include <base\EventStream.h>
#include <base\InputSystem.h>
#include <gen\MeshGen.h>
#include <gen\MeshGenCommand.h>
#include <utils\ObjLoader.h>
#include <renderer\graphics.h>
#include <utils\TileMapReader.h>
#include "..\Constants.h"
#include "..\utils\TileGrid.h"

const int SIZE_X = 8;
const int SIZE_Y = 8;



GeoTestState::GeoTestState() : ds::GameState("GeoTestState"), _name("base_house") , _gui(0) , _mesh(0) {
	_camera = (ds::FPSCamera*)ds::res::getCamera("fps");
	_orthoCamera = (ds::OrthoCamera*)ds::res::getCamera("ortho");
	_pressed = false;
}

GeoTestState::~GeoTestState() {
	_objects.destroy_all();
	if (_gui != 0) {
		delete _gui;
	}
	if (_mesh != 0) {
		delete _mesh;
	}
}

void GeoTestState::init() {
	//_camera->setPosition(v3(0, 2, -3), v3(0, 0, 0));
	//_camera->setPosition(v3(12, 6, -9), v3(0, 0, 1));
	//_camera->resetPitch(DEGTORAD(12.0f));
	//_camera->setYAngle(DEGTORAD(-45.0f));
	_camera->setPosition(v3(0.0f, 1.5f, -3.0f), v3(0.0f, 0.0f, 0.1f));
	_camera->resetPitch(DEGTORAD(25.0f));
	_mesh = new ds::Mesh();
	_material = ds::res::find("MeshMaterial", ds::ResourceType::MATERIAL);
	//_skyBox = ds::res::getSkyBox("SkyBox");

	_ctx.gen = &gen;
	_ctx.mesh = _mesh;

	_gui = new ds::gen::MeshGenGUI("ortho",&_ctx);

	LOG << " ======================================================== ";
	_scene = ds::res::getScene("TestObjects");
	_buffer = ds::res::getMeshBuffer("TexturedBuffer");
	
	char buffer[32];
	// ----------------------------------------
	// tower building test
	// ----------------------------------------
	buildTower(p2i(1, 1));
	buildTower(p2i(4, 1));
	// ----------------------------------------
	// house building test
	// ----------------------------------------
	/*
	int grid_dim = 10;
	SimpleGrid grid(10);
	int cell_size = 2;
	int cells = 3;
	int d = 10 - cell_size * cells;
	int offset = d / cell_size;
	int total = cells * 2;
	int step = grid_dim / cells;

	for (int i = 0; i < cells + 1; ++i) {
		int y = i * step;
		for (int x = 0; x < grid_dim; ++x) {
			grid.set(x, y, 2);
			grid.set(y, x, 2);
		}
	}
	for (int y = 0; y < cells; ++y) {
		for (int x = 0; x < cells; ++x) {
			//int sx = math::random(0, offset - 1) + x * 10 / cells;
			//int sy = math::random(0, offset - 1) + y * 10 / cells;
			int sx = x * step + 1;
			int sy = y * step + 1;
			grid.set(sx, sy, 3);
			grid.set(sx + 1, sy, 1);
			grid.set(sx, sy + 1, 1);
			grid.set(sx + 1, sy + 1, 1);
		}
	}
	
	for (int y = 0; y < grid_dim; ++y) {
		for (int x = 0; x < grid_dim; ++x) {
			if (grid.get(x, y) == 2) {
				int b = grid.adjacents(x, y);
				if (b != 0) {
					//LOG << "x: " << x << " y: " << y << " b: " << b;
					grid.set(x, y, 10 + b);
				}
			}
		}
	}


	for (int y = 0; y < grid_dim; ++y) {
		for (int x = 0; x < grid_dim; ++x) {
			if (grid.get(x, y) == 0) {
				buildGrass(p2i(-5 + x, 5 - y));
			}
			//if (grid.get(x,y) == 1) {
				//buildHouse(p2i(-5 + x, 5 - y));
			//}
			if (grid.get(x, y) == 3) {
				buildTower(p2i(-5 + x, 5 - y));
			}
			if (grid.get(x, y) == 2) {
				buildStreet(p2i(-5 + x, 5 - y),10);
			}
			if (grid.get(x,y) > 10 ) {
				buildStreet(p2i(-5 + x, 5 - y),grid.get(x,y) - 10);
			}
		}
	}
	*/
	/*
	for (int i = 0; i < 6; ++i) {
		buildHouse(p2i(-4+i, 0));
		buildStreet(p2i(-4+i, -1));
		buildHouse(p2i(-4 + i, -2));
	}
	*/
	//buildStreet(p2i(0, 0), 5);
	//buildStreet(p2i(0, 0));

	// ----------------------------------------
	// scale test
	// ----------------------------------------
	/*
	v3 p[] = { v3(-0.5f, 0.5f, 0.0f), v3(0.5f, 0.5f, 0.0f), v3(0.5f, -0.5f, 0.0f), v3(-0.5f, -0.5f, 0.0f) };
	gen.add_face(p);
	gen.slice(0, 3);
	uint16_t adjacents[] = { 0, 2, 8, 6 };
	gen.expand_face(4, adjacents, 0.2f, 0.2f);
	gen.debug_colors();
	*/
	//uint16_t f = gen.add_cube(v3(0.0f, 0.0f, 0.0f), v3(1.0f, 1.0f, 1.0f));
	/*
	gen.startGroup();
	gen.create_cylinder(v3(0, 0, 0), 0.5f, 0.5f, 1.0f, 16);
	gen.endGroup();
	gen.rotateGroup(0, v3(DEGTORAD(90.0f), 0.0f, 0.0f));
	gen.cut(v3(0.0f, 0.0f, 0.0f), v3(0, 1, 0));
	*/
	/*
	gen.set_color_selection(ds::Color(162, 132, 101, 255));
	gen.startGroup();
	gen.create_tube(v3(0, 0, 0), 1.0f, 1.0f, 1.0f, 0.2f, 16);
	gen.endGroup();
	gen.rotateGroup(0, v3(DEGTORAD(90.0f), 0.0f, 0.0f));
	gen.cut(v3(0.0f, 0.0f, 0.0f), v3(0, 1, 0));
	*/
	//gen.set_color_selection(ds::Color(221, 207, 190, 255));
	//gen.create_sphere(v3(0, 0, 0), 0.4f, 9, 9);
	//gen.cut(v3(0.0f, 0.0f, 0.0f), v3(0, 1, 0), false);
	//gen.debug_colors();
	//gen.debug_colors();
	//createHandrail(6.0f, 0.1f, 7 , 0.6f);
	//createCoords();
	//v3 p[] = {v3(-6.0f,-0.6f,6.0f),v3(6.0f,-0.6f,6.0f),v3(6.0f,-0.6f,-6.0f),v3(-6.0f,-0.6f,-6.0f)};
	//v3 p[] = { v3(-1,1,0), v3(1,1,0),v3(1,-1,0),v3(-1,-1,0) };
	/*
	uint16_t f = gen.add_cube(v3(0.0f, 0.0f, 0.0f), v3(1.0f, 0.1f, 1.0f));	
	gen.vsplit_edge(19, 0.4f);
	gen.vsplit_edge(27, 0.33f);
	gen.move_edge(24, v3(0.0f, 0.4f, 0.0f));
	gen.move_edge(26, v3(0.0f, 0.4f, 0.0f));
	uint16_t edges[] = { 25, 29, 4, 17 };
	gen.make_face(edges);
	uint16_t edges2[] = { 27, 19, 12, 31};
	gen.make_face(edges2);
	gen.save_text("roof_0");
	gen.save_bin("roof_0");
	gen.clear();
	*/
	//gen.load_text("roof_0");
	//gen.load_text(_name);
	//gen.scale_face(6, 0.5f);
	/*
	uint16_t slices[45];
	int num = gen.slice(0, 9, 5, slices, 32);
	for (int i = 0; i < 5; ++i) {
		uint16_t ei = gen.get_edge(23 + i * 2, 0);
		gen.move_edge(ei, v3(0.0f, 0.1f, 0.0f));
	}
	for (int i = 0; i < 5; ++i) {
		uint16_t ei = gen.get_edge(32 + i * 2, 0);
		gen.move_edge(ei, v3(0.0f, -0.1f, 0.0f));
	}
	for (int i = 0; i < 3; ++i) {
		uint16_t ei = gen.get_edge(7 + i * 18, 3);
		gen.move_edge(ei, v3(-0.05f, 0.0f, 0.0f));
	}
	for (int i = 0; i < 3; ++i) {
		uint16_t ei = gen.get_edge(7 + i * 18, 1);
		gen.move_edge(ei, v3(0.05f, 0.0f, 0.0f));
	}
	for (int i = 0; i < 3; ++i) {
		uint16_t ei = gen.get_edge(11 + i * 18, 3);
		gen.move_edge(ei, v3(-0.05f, 0.0f, 0.0f));
	}
	for (int i = 0; i < 3; ++i) {
		uint16_t ei = gen.get_edge(11 + i * 18, 1);
		gen.move_edge(ei, v3(0.05f, 0.0f, 0.0f));
	}
	for (int i = 0; i < num + 5; ++i) {
		gen.set_color(i, ds::Color(255, 252, 234, 255));
	}
	uint16_t roof = gen.add_cube(v3(0.0f, 1.05f, 0.0f), v3(1.2f, 0.1f, 1.2f));
	ds::gen::IndexList il;
	gen.find_adjacent_faces(roof, il);
	for (int i = 0; i < il.indices.size(); ++i) {
		gen.set_color(il.indices[i], ds::Color(58, 58, 58, 255));
	}
	//uint16_t re = gen.get_edge_index(il.indices[5], 3);
	uint16_t srf = gen.vsplit_edge(219);
	uint16_t sre = gen.get_edge_index(srf, 0);
	LOG << " SRF: " << srf << " SRE: " << sre;
	gen.move_edge(sre, v3(0.0f, 1.0f, 0.0f));
	gen.save_bin("House_base");
	gen.clear();
	gen.load_bin("House_base");
	ds::TileMapReader colorDefs;
	if (colorDefs.parse("content\\house_colors.txt")) {
		int tiles = colorDefs.height() / 5;
		for (int i = 0; i < tiles; ++i) {
			sprintf_s(buffer, 32, "house_%d", i);
			int offset = i * 45;
			int t = 4;
			for (int j = 0; j < 45; ++j) {
				if (j == 0) {
					t = 4;
				}
				else {
					t = 5 + j;
				}
				if (colorDefs.get(offset + j) == 0) {
					gen.set_color(t, ds::Color(255, 252, 234, 255));
				}
				else if (colorDefs.get(offset + j) == 1) {
					gen.set_color(t, ds::Color(157, 98, 66, 255));
				}
				else if (colorDefs.get(offset + j) == 2) {
					gen.set_color(t, ds::Color(153, 217, 234, 255));
				}
				else if (colorDefs.get(offset + j) == 3) {
					gen.set_color(t, ds::Color(58, 58, 58, 255));
				}
			}
			gen.save_mesh(buffer);
		}
	}
	*/
	//gen.load_text("roof_0");
	//gen.save_mesh("roof_0");
	//gen.clear();
	//gen.load_text("window_0");
	//createWindow(v3(0,0,0));
	/*
	gen.add_cube(v3(0, 0, 0), v3(1.0f,0.6f,1.0f));
	gen.build(_mesh);
	_mesh->load("window_1", v3(-0.25f, 0.0f, -0.54f));
	_mesh->load("window_1", v3(0.25f, 0.0f, -0.54f));
	_mesh->load("roof_0", v3(0.0f, 0.35f, 0.0f));
	ID id = _scene->add(_mesh, v3(0, 0, 0));
	_mesh->buildBoundingBox();
	_mesh->save("house_0");
	*/
	//buildTestTerrain();
	//buildTerrain();
	//gen.add_cube(v3(0, 0, 0), v3(1.0f, 0.1f, 1.0f));
	//gen.extrude_face(4, 0.5f);
	//gen.scale_face(6, 0.2f);
	//gen.extrude_face(6, 0.3f);
	/*
	gen.add_cube(v3(0.0f, 0.35f, 0.0f), v3(1.0f, 0.6f, 1.0f));
	//gen.slice(0, 3);
	gen.scale_face(10, 0.1f);
	gen.add_cube(v3(0.0f, 0.70f, 0.0f), v3(1.2f, 0.1f, 1.2f));
	gen.hsplit_edge(64, 0.45f);
	gen.hsplit_edge(72, 0.05f);
	gen.move_edge(65, v3(0.0f, 0.4f, 0.0f));
	gen.move_edge(79, v3(0.0f, 0.4f, 0.0f));
	gen.hsplit_edge(68, 0.45f);
	*/
	//gen.move_edge(81, v3(0.0f, 0.4f, 0.0f));
	//gen.debug_colors();
	//gen.load_text(_name);
	//gen.build(_mesh);
	//ID id = _scene->add(_mesh, v3(0, 0, 0));
	//_mesh->save("house_0");
	//buildTerrain();
	/*
	for (int i = 0; i < 16; ++i) {
		createTile(i, i);
		sprintf_s(buffer, 32, "tile_%d", i );
		ds::Mesh* m = new ds::Mesh();
		m->load(buffer);
		_objects.push_back(m);
	}
	float sx = -2.5f;
	float sy = 0.0f;
	float sz = 0.0f;
	int cnt = 0;
	for (int z = 0; z < 3; ++z) {
		for (int x = 0; x < 5; ++x) {
			_scene->add(_objects[cnt++], v3(sx + x, sy, sz + z));
		}
	}
	*/
}





// ------------------------------------------
// build terrain
// ------------------------------------------
void GeoTestState::buildTerrain() {
	char buffer[32];
	for (int i = 0; i < 12; ++i) {
		sprintf_s(buffer, 32, "tile_%d", i);
		ds::Mesh* m = new ds::Mesh();
		m->load(buffer);
		_objects.push_back(m);
	}
	for (int i = 0; i < 1; ++i) {
		sprintf_s(buffer, 32, "house_%d", i);
		ds::Mesh* m = new ds::Mesh();
		m->load(buffer);
		_objects.push_back(m);
	}
	for (int i = 0; i < 2; ++i) {
		sprintf_s(buffer, 32, "tree_%d", i);
		ds::Mesh* m = new ds::Mesh();
		m->load(buffer);
		_objects.push_back(m);
	}
	ds::TileMapReader reader;
	reader.parse("content\\field.txt");
	float sx = reader.width() * 0.5f - 0.5f;
	float sy = -3.0f;
	float sz = reader.height() * 0.5f + 2;
	for (int y = reader.height() - 1; y >= 0; --y) {
		for (int x = 0; x < reader.width(); ++x) {
			int index = reader.get(x, y);
			ID id = _scene->add(_objects[index], v3(-sx + x, sy, sz - y),_material);
			_ids.push_back(id);
		}
	}
}

// ------------------------------------------
// build TEST terrain
// ------------------------------------------
void GeoTestState::buildTestTerrain() {
	ds::Mesh* m = new ds::Mesh();
	m->load("tile_0");
	_objects.push_back(m);
	float sx = 3.0f * 0.5f - 0.5f;
	float sy = 3.0f * 0.5f + 2;
	for (int y = 3 - 1; y >= 0; --y) {
		for (int x = 0; x < 3; ++x) {
			_scene->add(m, v3(-sx + x, -3, sy - y),_material);
		}
	}
}

void GeoTestState::createHandrail(float length, float griderSize, int segments, float height) {
	uint16_t faces[16];
	int cnt = 0;
	faces[cnt++] = gen.add_cube(v3(0, 0, 0), v3(length, griderSize, griderSize), v3(DEGTORAD(45.0f), 0.0f, 0.0f));
	int s = (segments - 1) / 2;
	float il = (length - griderSize * 4.0f);
	float step = il * 0.5f / s;	
	for (int i = -s; i < s + 1; ++i) {
		faces[cnt++] = gen.add_cube(v3(step * i, -height * 0.5f - griderSize * 0.5f, 0.0f), v3(griderSize, height, griderSize));
	}
	for (int i = 0; i < cnt; ++i) {
		gen.set_color(faces[i], ds::Color(128, 128, 128, 255));
	}
	//gen.save_bin("Test.data");
	//gen.save_text("Test.txt");
	gen.save_mesh("handrail");
}

void GeoTestState::createCoords() {
	// coordsystem
	uint16_t faces[6];
	gen.add_cube(v3(0.5f, 0.0f, 0.0f), v3(1.0f, 0.1f, 0.1f), faces);
	for (int i = 0; i < 6; ++i) {
		gen.set_color(faces[i], ds::Color(255, 0, 0, 255));
	}
	gen.add_cube(v3(0.05f, 0.5f, 0.0f), v3(0.1f, 0.9f, 0.1f), faces);
	for (int i = 0; i < 6; ++i) {
		gen.set_color(faces[i], ds::Color(0, 255, 0, 255));
	}
	gen.add_cube(v3(0.05f, 0.0f, 0.5f), v3(0.1f, 0.1f, 0.9f), faces);
	for (int i = 0; i < 6; ++i) {
		gen.set_color(faces[i], ds::Color(0, 0, 255, 255));
	}
}

void GeoTestState::createGriderBox(ds::gen::MeshGen* gen, float dim, float griderSize) {
	float size = dim;
	float hs = size * 0.5f;
	float w = griderSize;
	float hw = w * 0.5f;
	gen->add_cube(v3(-hs + hw, 0.0f,-hs + hw), v3(w, size, w));
	gen->add_cube(v3( hs - hw, 0.0f,-hs + hw), v3(w, size, w));
	gen->add_cube(v3(-hs + hw, 0.0f, hs - hw), v3(w, size, w));
	gen->add_cube(v3( hs - hw, 0.0f, hs - hw), v3(w, size, w));

	gen->add_cube(v3(0.0f, hs - hw, hs - hw), v3(size - 2.0f * w, w, w));
	gen->add_cube(v3(0.0f,-hs + hw,-hs + hw), v3(size - 2.0f * w, w, w));
	gen->add_cube(v3(0.0f, hs - hw,-hs + hw), v3(size - 2.0f * w, w, w));
	gen->add_cube(v3(0.0f,-hs + hw, hs - hw), v3(size - 2.0f * w, w, w));

	gen->add_cube(v3( hs - hw,-hs + hw, 0.0f), v3(w, w, size - 2.0f * w));
	gen->add_cube(v3( hs - hw, hs - hw, 0.0f), v3(w, w, size - 2.0f * w));
	gen->add_cube(v3(-hs + hw,-hs + hw, 0.0f), v3(w, w, size - 2.0f * w));
	gen->add_cube(v3(-hs + hw, hs - hw, 0.0f), v3(w, w, size - 2.0f * w));
}
// -------------------------------------------------------
// update
// -------------------------------------------------------
int GeoTestState::update(float dt) {
	_camera->update(dt);	
	_gui->handleClick(_camera);
	/*
	if (ds::input::isMouseButtonPressed(0) && !_pressed) {
		_pressed = true;
		ds::Ray r = graphics::getCameraRay(_camera);
		ID id = _scene->intersects(r);
	}
	if (!ds::input::isMouseButtonPressed(0) && _pressed) {
		_pressed = false;
	}
	*/
	return 0;
}

// -------------------------------------------------------
// render
// -------------------------------------------------------
void GeoTestState::render() {
	// scene
	graphics::setCamera(_camera);
	graphics::turnOffZBuffer();
	//_skyBox->render();
	graphics::turnOnZBuffer();
	_scene->draw();
	//_gui->drawGUI();
}

// -------------------------------------------------------
// drawGUI
// -------------------------------------------------------
void GeoTestState::drawGUI() {
	graphics::setCamera(_orthoCamera);
	graphics::turnOffZBuffer();
	v2 pos(10, 760);
	int state = 1;
	gui::start(1, &pos, true);
	gui::begin("Camera", &state);
	char buffer[128];
	sprintf_s(buffer, 128, "%2.2f %2.2f %2.2f", _camera->getPosition().x, _camera->getPosition().y, _camera->getPosition().z);
	gui::Value("Pos", buffer);
	gui::Value("Yaw", RADTODEG(_camera->getYaw()));
	gui::Value("Pitch", RADTODEG(_camera->getPitch()));
	if (gui::Button("Reset")) {
		_camera->setPosition(v3(0, 0, -10), v3(0, 0, 1));
		_camera->resetYAngle();
	}
	gui::end();
}

// -------------------------------------------
// Create street tiles
// -------------------------------------------
void GeoTestState::createTile(int index, int directions) {
	ds::gen::MeshGen g;
	g.load_text("base_tile");
	int colors[25];
	for (int i = 0; i < 25; ++i) {
		colors[i] = 0;
	}
	if (directions != 0) {
		colors[7] = 1;
		colors[11] = 1;
		colors[6] = 1;
		colors[8] = 1;
		colors[12] = 2;
		colors[13] = 1;		
		colors[17] = 1;
		colors[16] = 1;
		colors[18] = 1;
	}
	if ((directions & 1) != 0) {
		colors[1] = 1;
		colors[2] = 2;
		colors[3] = 1;
		colors[6] = 1;
		colors[7] = 2;
		colors[8] = 1;

	}
	if ((directions & 2) != 0) {
		colors[8] = 1;
		colors[9] = 1;
		colors[13] = 2;
		colors[14] = 2;
		colors[18] = 1;
		colors[19] = 1;
	}
	if ((directions & 4) != 0) {
		colors[16] = 1;
		colors[17] = 2;
		colors[18] = 1;
		colors[21] = 1;
		colors[22] = 2;
		colors[23] = 1;
	}
	if ((directions & 8) != 0) {
		colors[6] = 1;
		colors[11] = 2;
		colors[16] = 1;
		colors[5] = 1;
		colors[10] = 2;
		colors[15] = 1;
	}
	if (directions != 0) {
		colors[12] = 2;
	}
	for (int j = 0; j < 25; ++j) {
		if (colors[j] == 0) {
			g.set_color(j, GRASS);
		}
		else if (colors[j] == 1) {
			g.set_color(j, CURBS);
		}
		if (colors[j] == 2) {
			g.set_color(j, STREET);
		}
	}
	char fileName[32];
	sprintf_s(fileName, 32, "tile_%d", index);
	g.save_mesh(fileName);
}

void GeoTestState::createStreets() {
	char buffer[32];
	ds::TileMapReader colorDefs;
	if (colorDefs.parse("content\\tile_colors.txt")) {
		int tiles = colorDefs.height() / 5;
		for (int i = 0; i < tiles; ++i) {
			gen.clear();
			uint16_t f = gen.add_cube(v3(0.0f, 0.0f, 0.0f), v3(1.0f, 0.1f, 1.0f));
			uint16_t slices[45];
			int num = gen.slice(4, 5, slices, 32);
			gen.move_edge(25, v3(-0.1f, 0.0f, 0.0f));
			gen.move_edge(65, v3(-0.1f, 0.0f, 0.0f));
			gen.move_edge(105, v3(-0.1f, 0.0f, 0.0f));

			gen.move_edge(35, v3(0.1f, 0.0f, 0.0f));
			gen.move_edge(75, v3(0.1f, 0.0f, 0.0f));
			gen.move_edge(115, v3(0.1f, 0.0f, 0.0f));

			gen.move_edge(42, v3(0.0f, 0.0f, 0.1f));
			gen.move_edge(50, v3(0.0f, 0.0f, 0.1f));
			gen.move_edge(58, v3(0.0f, 0.0f, 0.1f));

			gen.move_edge(62, v3(0.0f, 0.0f, -0.1f));
			gen.move_edge(70, v3(0.0f, 0.0f, -0.1f));
			gen.move_edge(78, v3(0.0f, 0.0f, -0.1f));

			gen.set_color(0, ds::Color(157, 98, 66, 255));
			gen.set_color(1, ds::Color(157, 98, 66, 255));
			gen.set_color(2, ds::Color(157, 98, 66, 255));
			gen.set_color(3, ds::Color(157, 98, 66, 255));
			gen.set_color(5, ds::Color(157, 98, 66, 255));
			gen.recalculate_normals();

			sprintf_s(buffer, 32, "tile_%d", i);
			int offset = i * 25;
			for (int j = 0; j < num; ++j) {
				if (colorDefs.get(offset + j) == 0) {
					gen.set_color(slices[j], ds::Color(184, 203, 98, 255));
				}
				else if (colorDefs.get(offset + j) == 1) {
					gen.set_color(slices[j], ds::Color(223, 215, 204, 255));
				}
				if (colorDefs.get(offset + j) == 2) {
					gen.set_color(slices[j], ds::Color(151, 144, 138, 255));
				}
			}
			gen.save_text(buffer);
			gen.save_mesh(buffer);
		}
	}
}

void GeoTestState::createWindow(const v3& center) {
	ds::gen::MeshGen wgen;
	float size = 0.4f;
	float hs = size * 0.5f;
	float w = 0.04f;
	float hw = w * 0.5f;
	wgen.add_cube(v3(center.x - hs + hw, 0.0f, center.z), v3(w, size, w));
	wgen.add_cube(v3(center.x + hs - hw, 0.0f, center.z), v3(w, size, w));
	wgen.add_cube(v3(center.x, hs - hw, center.z), v3(size - 2.0f * w, w, w));
	wgen.add_cube(v3(center.x, -hs + hw, center.z), v3(size - 2.0f * w, w, w));
	v3 p[] = {
		v3(center.x - hs + hw * 2.0f,hs -hw,center.z + hw),
		v3(center.x + hs - hw * 2.0f,hs - hw,center.z + hw),
		v3(center.x + hs - hw * 2.0f,-hs +hw,center.z + hw),
		v3(center.x - hs + hw * 2.0f,-hs + hw,center.z + hw) };
	uint16_t window = wgen.add_face(p);
	for (int i = 0; i < wgen.num_faces(); ++i) {
		wgen.set_color(i, ds::Color(157, 98, 66, 255));
	}
	wgen.set_color(window, ds::Color(196, 215, 213, 255));
	wgen.save_mesh("window_1");
}

// ----------------------------------------------------------
// build grass
// ----------------------------------------------------------
void GeoTestState::buildGrass(const p2i& gridPos) {
	ds::Mesh* m = new ds::Mesh;
	gen.clear();
	gen.set_color_selection(GRASS);
	v3 gp[] = { v3(-0.5f,0.0f,0.5f),v3(0.5f,0.0f,0.5f),v3(0.5f,0.0f,-0.5f),v3(-0.5f,0.0f,-0.5f) };
	gen.add_face(gp);
	gen.recalculate_normals();
	gen.build(m);
	float sx = gridPos.x;
	float sz = gridPos.y;
	_scene->addStatic(m, v3(sx, 0.0f, sz),_material);
	_objects.push_back(m);
}
// ----------------------------------------------------------
// build house
// ----------------------------------------------------------
void GeoTestState::buildHouse(const p2i& gridPos) {
	ds::Mesh* m = new ds::Mesh;
	gen.clear();
	static ds::Color house_colors[] = { ds::Color(206, 122, 106, 255) , ds::Color(201,165,109,255), ds::Color(160,149,120,255) };
	int floors = math::random(1.0f, 3.9f);
	float h = 0.0f;
	int cnr = math::random(0.0f, 2.9f);
	gen.set_color_selection(GRASS);
	v3 gp[] = { v3(-0.5f,0.0f,0.5f),v3(0.5f,0.0f,0.5f),v3(0.5f,0.0f,-0.5f),v3(-0.5f,0.0f,-0.5f) };
	gen.add_face(gp);
	for (int i = 0; i < floors; ++i) {		
		gen.set_color_selection(house_colors[cnr]);
		uint16_t wf[6];
		uint16_t num = gen.add_cube(v3(0.0f, h + 0.3f, 0.0f), v3(0.8f, 0.6f, 0.8f), wf);
		buildWall(gen, wf[0]);
		buildWall(gen, wf[1]);
		h += 0.6f;
		// roof
		gen.set_color_selection(ds::Color(213, 207, 197, 255));
		uint16_t rf = gen.add_cube(v3(0.0f, h + 0.05f, 0.0f), v3(0.8f, 0.1f, 0.8f));
		uint16_t roof_faces[9];
		uint16_t rsf = gen.slice(rf + 4, 3, 3, roof_faces, 9);
		uint16_t af[] = { roof_faces[0],roof_faces[2],roof_faces[8],roof_faces[6] };
		gen.expand_face(roof_faces[4], af, 0.2f, 0.2f);
		gen.extrude_face(roof_faces[4], -0.09f);
		gen.remove_face(roof_faces[4]);
		h += 0.1f;
	}
	//gen.debug_colors();
	gen.recalculate_normals();
	gen.build(m);
	float sx = gridPos.x;// *0.5f;
	float sz = gridPos.y;// *0.5f;
	_scene->addStatic(m, v3(sx, 0.0f, sz),_material);
	_objects.push_back(m);
}

// ----------------------------------------------------------
// build wall
// ----------------------------------------------------------
void GeoTestState::buildWall(ds::gen::MeshGen& gen, int face_idx) {
	int wi_nr = math::random(1.0f, 3.9f);
	uint16_t wsf[32];
	uint16_t ewf[6];
	if (wi_nr == 1) {
		uint16_t nrs = gen.slice(face_idx, 3, 3, wsf, 32);
		uint16_t af[] = { wsf[0],wsf[2],wsf[8],wsf[6] };
		gen.expand_face(wsf[4], af, 0.2f, 0.1f);
		uint16_t nw = gen.extrude_face(wsf[4], -0.05f, ewf);
		gen.set_color(ewf[0], ds::Color(190, 210, 214, 255));
		gen.remove_face(wsf[4]);
	}
	else {
		int sl = (wi_nr - 1) * 2 + 1;
		uint16_t nrs = gen.slice(face_idx, sl, 3, wsf, 32);
		for (int j = 0; j < wi_nr - 1; ++j) {
			uint16_t nw = gen.extrude_face(wsf[sl + 1 + j * 2], -0.05f, ewf);
			gen.set_color(ewf[0], ds::Color(190, 210, 214, 255));
			gen.remove_face(wsf[sl + 1 + j * 2]);
		}
	}
}

// ----------------------------------------------------------
// build street
// ----------------------------------------------------------
void GeoTestState::buildStreet(const p2i& gridPos, int bits) {
	ds::Mesh* m = new ds::Mesh;
	gen.clear();
	int cnr = math::random(0.0f, 2.9f);
	gen.set_color_selection(GRASS);
	v3 gp[] = { v3(-0.5f, 0.0f, 0.5f), v3(0.5f, 0.0f, 0.5f), v3(0.5f, 0.0f, -0.5f), v3(-0.5f, 0.0f, -0.5f) };
	gen.add_face(gp);
	uint16_t faces[25];
	gen.slice(0, 5, 5, faces, 25);
	v3 dir[] = { v3(0.0f, 0.0f, 0.1f), v3(0.0f, 0.0f, -0.1f), v3(-0.1f, 0.0f, 0.0f), v3(0.1f, 0.0f, 0.0f) };
	for (int i = 0; i < 3; ++i) {
		uint16_t ei = gen.get_edge(faces[10 + i * 2], 0);
		gen.move_edge(ei, dir[0]);
		ei = gen.get_edge(faces[15 + i * 2], 0);
		gen.move_edge(ei, dir[1]);
		ei = gen.get_edge(faces[2 + i * 10], 3);
		gen.move_edge(ei, dir[2]);
		ei = gen.get_edge(faces[2 + i * 10], 1);
		gen.move_edge(ei, dir[3]);
	}

	TileGrid tg(5);
	int offsets[] = { 2, 7, 13, 14, 17, 22, 10, 11 };
	for (int i = 0; i < 4; ++i) {
		if ((bits & 1 << i) == 1 << i) {
			tg.toggle(offsets[i * 2]);
			tg.toggle(offsets[i * 2 + 1]);
		}
	}
	if (bits > 0) {
		tg.toggle(12);
	}
	gen.set_color_selection(CURBS);
	int fa[9];
	uint16_t ef[6];
	for (int y = 0; y < 5; ++y) {
		for (int x = 0; x < 5; ++x) {
			if (tg.isUsed(x, y)) {
				int n = tg.free_adjacents(x, y, fa);
				if (n > 0) {
					for (int k = 0; k < n; ++k) {
						gen.set_color(faces[fa[k]], CURBS);
					}
				}
			}
		}
	}
	for (int y = 0; y < 5; ++y) {
		for (int x = 0; x < 5; ++x) {
			if (tg.isUsed(x, y)) {
				int i = x + y * 5;
				gen.extrude_face(faces[i], -0.04f, ef);
				gen.remove_face(faces[i]);
				if (!tg.isValid(x, y - 1) || tg.isUsed(x, y - 1)) {
					gen.remove_face(ef[1]);
					//gen.set_color(ef[1], ds::Color(255, 0, 0));
				}
				if (!tg.isValid(x, y + 1) || tg.isUsed(x, y + 1)) {
					gen.remove_face(ef[3]);
					//gen.set_color(ef[3], ds::Color(0, 255, 0));
				}
				if (!tg.isValid(x - 1, y) || tg.isUsed(x - 1, y)) {
					gen.remove_face(ef[2]);
					//gen.set_color(ef[2], ds::Color(0, 0, 255));
				}
				if (!tg.isValid(x + 1, y) || tg.isUsed(x + 1, y)) {
					gen.remove_face(ef[4]);
					//gen.set_color(ef[4], ds::Color(255, 0, 255));
				}
				gen.set_color(ef[0], STREET);
			}
		}
	}
	//gen.debug_colors();
	gen.recalculate_normals();
	gen.build(m);
	float sx = gridPos.x;
	float sz = gridPos.y;
	_scene->addStatic(m, v3(sx, 0.0f, sz),_material);
	_objects.push_back(m);
}

void GeoTestState::buildHouse(const House& house) {
	for (int y = 0; y < 2; ++y) {
		for (int x = 0; x < 2; ++x) {
			for (int h = 0; h < 5; ++h) {

			}
		}
	}
}

void GeoTestState::buildTower(const p2i& gridPos) {
	ds::Mesh* m = new ds::Mesh;
	gen.clear();
	House h;
	int gx = math::random(0.0f, 1.9f);
	//gx = 0;
	float xp = gx * 0.5f;
	int gy = math::random(0.0f, 1.9f);
	float yp = gy * 0.5f;
	h.pos = p2i(gx, gy);
	h.tiles[gx][gy][0] = 1;
	int nx = gx == 0 ? 1 : 0;
	h.tiles[nx][gy][0] = 1;
	int ny = gy == 0 ? 1 : 0;
	h.tiles[gx][ny][0] = 1;
	for (int y = 0; y < 2; ++y) {
		for (int x = 0; x < 2; ++x) {
			if (h.tiles[x][y][0] == 1) {
				int k = math::random(1.0f, 3.9f);
				h.colors[x][y] = math::random(0.0f, 2.9f);
				for (int i = 0; i < k; ++i) {
					h.tiles[x][y][i] = 1;
				}
			}
		}
	}
	static ds::Color house_colors[] = { ds::Color(206, 122, 106, 255), ds::Color(201, 165, 109, 255), ds::Color(160, 149, 120, 255) };
	uint16_t wf[6];	
	for (int y = 0; y < 2; ++y) {
		for (int x = 0; x < 2; ++x) {
			float height = 0.0f;
			float xp = gridPos.x + 0.1f + x * 0.8f;
			float zp = gridPos.y + 0.1f + y * 0.8f;
			for (int k = 0; k < 5; ++k) {				
				float yp = k * 0.6f;
				if (h.tiles[x][y][k] == 1) {
					gen.set_color_selection(house_colors[h.colors[x][y]]);
					
					uint16_t num = gen.add_cube(v3(xp,yp,zp), v3(0.8f, 0.6f, 0.8f), wf);
					height += 0.6f;
					if (y == 1) {
						if (h.tiles[x][y - 1][k] != 1) {
							buildWall(gen, wf[0]);
						}
					}
					else {
						buildWall(gen, wf[0]);
					}

					if (x == 0) {
						if (h.tiles[x + 1][y][k] != 1) {
							buildWall(gen, wf[1]);
						}
					}
					else {
						buildWall(gen, wf[1]);
					}
				}				
			}
			if (height > 0.0f) {
				gen.set_color_selection(ds::Color(213, 207, 197, 255));
				uint16_t rf = gen.add_cube(v3(xp, height - 0.25f, zp), v3(0.8f, 0.1f, 0.8f));
				uint16_t roof_faces[9];
				uint16_t rsf = gen.slice(rf + 4, 3, 3, roof_faces, 9);
				uint16_t af[] = { roof_faces[0], roof_faces[2], roof_faces[8], roof_faces[6] };
				gen.expand_face(roof_faces[4], af, 0.2f, 0.2f);
				gen.extrude_face(roof_faces[4], -0.09f);
				gen.remove_face(roof_faces[4]);
			}
		}
	}
	//gen.debug_colors();
	gen.recalculate_normals();
	gen.build(m);
	float sx = gridPos.x;
	float sz = gridPos.y;
	_scene->addStatic(m, v3(sx, 0.0f, sz),_material);
	_objects.push_back(m);
}
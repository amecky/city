#include "MeshGenTestState.h"
#include <utils\Log.h>
#include <base\EventStream.h>
#include <base\InputSystem.h>
#include <gen\MeshGen.h>
#include <gen\MeshGenCommand.h>
#include <utils\ObjLoader.h>
#include <renderer\graphics.h>
#include <utils\TileMapReader.h>
#include <utils\FileUtils.h>

MeshGenTestState::MeshGenTestState(const char* meshName, ds::Game* game) : ds::GameState("MeshGenTestState", game), _name(meshName), _mesh(0), _grid(0), _offset(0), _switch(false) {
	for (int i = 0; i < 4; ++i) {
		_squares[i] = 0;
	}
}


MeshGenTestState::~MeshGenTestState() {
	if (_grid != 0) {
		delete _grid;
	}
	for (int i = 0; i < 4; ++i) {
		if (_squares[i] != 0) {
			delete _squares[i];
		}
	}
	if (_mesh != 0) {
		delete _mesh;
	}
}

// -------------------------------------------------------
// init
// -------------------------------------------------------
void MeshGenTestState::init() {
	_camera = graphics::getFPSCamera();
	_camera->setPosition(v3(0, 3, -6), v3(0.0f, 0.0f, 0.1f));
	_camera->resetPitch(DEGTORAD(25.0f));
	_orthoCamera = graphics::getOrthoCamera();
	_scene = ds::res::getScene("TestObjects");
	_pressed = false;
	_mesh = new ds::Mesh();
	_grid = new ds::Mesh();
	_grid->load("grid");
	_material = ds::res::find("MeshMaterial", ds::ResourceType::MATERIAL);
	// build squares to show vertices of the selected face
	ds::gen::MeshGen g;
	g.add_cube(v3(0, 0, 0), v3(0.1f, 0.1f, 0.1f));
	ds::Color clrs[] = { ds::Color(255,0,0,255),ds::Color(0,255,0,255),ds::Color(0,0,255,255),ds::Color(255,0,255,255) };
	for (int i = 0; i < 4; ++i) {
		_squares[i] = new ds::Mesh;
		for (int j = 0; j < 6; ++j) {
			g.set_color(j, clrs[i]);
		}
		g.build(_squares[i]);
		_square_ids[i] = _scene->add(_squares[i], v3(i * 1, 0, 0), _material);
		_scene->deactivate(_square_ids[i]);
	}	
	gen.load_text(_name);
	gen.build(_mesh);
	_grid_id = _scene->add(_grid, v3(0.0f, -0.01f, 0.0f), _material);
	_scene->deactivate(_grid_id);
	ID id = _scene->add(_mesh, v3(0, 0, 0), _material);
	_mesh->save(_name);

	LOG << "'1' : reload";
	LOG << "'2' : debug";
	LOG << "'3' : toggle grid";
	LOG << "'4' : save mesh";

	std::vector<std::string> files;
	ds::file::listDirectory("resources\\meshes", files);
	for (size_t i = 0; i < files.size(); ++i) {
		LOG << "file: " << files[i];
		std::string shortName = files[i];
		size_t idx = shortName.find('.');
		shortName = shortName.substr(0, idx);
		_model.add(shortName.c_str(),i);
	}
}

void MeshGenTestState::activate() {
	_camera->setPosition(v3(0, 3, -6), v3(0.0f, 0.0f, 0.1f));
	_camera->resetPitch(DEGTORAD(25.0f));
	_camera->resetYaw(0.0f);
}
// -------------------------------------------------------
// update
// -------------------------------------------------------
int MeshGenTestState::update(float dt) {
	_camera->update(dt);	
	if (ds::input::isMouseButtonPressed(0) && !_pressed) {
		_pressed = true;
		ds::Ray r = graphics::getCameraRay(_camera);
		int selection = gen.intersects(r);
		if (selection != -1) {
			bool selected = gen.select_face(selection);
			_mesh->clear();
			gen.build(_mesh);
			gen.debug_face(selection);
			v3 p[4];
			const ds::gen::Face& f = gen.get_face(selection);
			gen.get_vertices(f, p);
			for (int i = 0; i < 4; ++i) {
				_scene->setPosition(_square_ids[i],p[i]);
				if (selected) {
					_scene->activate(_square_ids[i]);
				}
				else {
					_scene->deactivate(_square_ids[i]);
				}
			}
		}
		else {
			showSelectionCubes(false);
		}
	}
	if (!ds::input::isMouseButtonPressed(0) && _pressed) {
		_pressed = false;
	}
	if (_switch) {
		_switch = false;
		return 1;
	}
	return 0;
}

// -------------------------------------------------------
// show or hide selection cubes
// -------------------------------------------------------
void MeshGenTestState::showSelectionCubes(bool active) {
	for (int i = 0; i < 4; ++i) {
		if (active) {
			_scene->activate(_square_ids[i]);
		}
		else {
			_scene->deactivate(_square_ids[i]);
		}
	}
}

// -------------------------------------------------------
// render
// -------------------------------------------------------
void MeshGenTestState::render() {
	_scene->draw();
	drawGUI();
}

void MeshGenTestState::drawGUI() {
	graphics::setCamera(_orthoCamera);
	graphics::turnOffZBuffer();
	v2 pos(10, 760);
	int state = 1;
	gui::start(1, &pos, true);
	gui::begin("Editor", &state);
	gui::beginGroup();
	if (gui::Button("Reload")) {
		LOG << "reloading " << _name;
		gen.load_text(_name);
		_mesh->clear();
		gen.build(_mesh);
		showSelectionCubes(false);
	}
	if (gui::Button("Debug")) {
		gen.debug();
	}
	if (gui::Button("Grid")) {
		bool active = _scene->isActive(_grid_id);
		if (active) {
			_scene->deactivate(_grid_id);
		}
		else {
			_scene->activate(_grid_id);
		}
	}
	if (gui::Button("Save")) {
		_mesh->save(_name);
		LOG << "Mesh saved";
	}
	if (gui::Button("World")) {
		_switch = true;
	}
	gui::endGroup();
	gui::end();
	gui::begin("Models", &state);
	gui::ComboBox(&_model, &_offset, 5);
	if (gui::Button("Load")) {
		if (_model.hasSelection()) {
			_name = _model.getLabel(_model.getSelection());
			LOG << "loading " << _name;
			gen.load_text(_name);
			_mesh->clear();
			gen.build(_mesh);
		}
	}	
	gui::end();
}

// -------------------------------------------------------
// onChar
// -------------------------------------------------------
int MeshGenTestState::onChar(int ascii) {
	if (ascii == '1') {
		LOG << "reloading " << _name;
		gen.load_text(_name);
		_mesh->clear();
		gen.build(_mesh);
		showSelectionCubes(false);
	}
	if (ascii == '2') {
		gen.debug();
	}
	if (ascii == '3') {
		bool active = _scene->isActive(_grid_id);
		if (active) {
			_scene->deactivate(_grid_id);
		}
		else {
			_scene->activate(_grid_id);
		}
	}
	if (ascii == '4') {
		_mesh->save(_name);
		LOG << "Mesh saved";
	}
	if (ascii == '5') {
		LOG << "camera: " << DBG_V3(_camera->getPosition()) << " target: " << DBG_V3(_camera->getTarget());
	}
	return 0;
}

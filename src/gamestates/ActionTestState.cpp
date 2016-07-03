#include "ActionTestState.h"
#include <utils\Log.h>
#include <base\EventStream.h>
#include <base\InputSystem.h>
#include <gen\MeshGen.h>
#include <gen\MeshGenCommand.h>
#include <utils\ObjLoader.h>
#include <renderer\graphics.h>
#include <utils\TileMapReader.h>
#include <utils\FileUtils.h>

ActionTestState::ActionTestState() : ds::GameState("ActionTestState"), _mesh(0) , _offset(0) {
	
}


ActionTestState::~ActionTestState() {	
	if (_mesh != 0) {
		delete _mesh;
	}
}

// -------------------------------------------------------
// init
// -------------------------------------------------------
void ActionTestState::init() {
	_camera = (ds::FPSCamera*)ds::res::getCamera("fps");
	_camera->setPosition(v3(0, 3, -6), v3(0.0f, 0.0f, 0.1f));
	_camera->resetPitch(DEGTORAD(25.0f));
	_orthoCamera = (ds::OrthoCamera*)ds::res::getCamera("ortho");
	_scene = ds::res::getScene("TestObjects");
	_mesh = new ds::Mesh();

	_material = ds::res::find("MeshMaterial", ds::ResourceType::MATERIAL);
	// build squares to show vertices of the selected face
	ds::gen::MeshGen g;
	g.add_cube(v3(0, 0, 0), v3(1,1,1));
	g.debug_colors();
	g.build(_mesh);
	_id = _scene->add(_mesh, v3(0, 0, 0), _material);
}

void ActionTestState::activate() {
	_camera->setPosition(v3(0, 3, -6), v3(0.0f, 0.0f, 0.1f));
	_camera->resetPitch(DEGTORAD(25.0f));
	_camera->resetYaw(0.0f);
}
// -------------------------------------------------------
// update
// -------------------------------------------------------
int ActionTestState::update(float dt) {
	_camera->update(dt);	
	_scene->tick(dt);
	return 0;
}

// -------------------------------------------------------
// render
// -------------------------------------------------------
void ActionTestState::render() {
	_scene->draw();
	//drawGUI();
}

void ActionTestState::drawGUI() {
	graphics::setCamera(_orthoCamera);
	graphics::turnOffZBuffer();
	v2 pos(10, 760);
	int state = 1;
	gui::start(1, &pos, true);
	gui::begin("Editor", &state);
	gui::end();
	graphics::turnOnZBuffer();
}

// -------------------------------------------------------
// onChar
// -------------------------------------------------------
int ActionTestState::onChar(int ascii) {
	if (ascii == '1') {
		LOG << "camera: " << DBG_V3(_camera->getPosition()) << " target: " << DBG_V3(_camera->getTarget());
	}
	if (ascii == '2') {
		_scene->scaleTo(_id, v3(1, 1, 1), v3(0.5f, 0.5f, 0.5f), 0.5f, 0,tweening::easeSinus);
	}
	if (ascii == '3') {
		_scene->moveTo(_id, v3(-2,0,0), v3(2,0,0), 0.5f, 0, tweening::easeInOutCubic);
	}
	return 0;
}

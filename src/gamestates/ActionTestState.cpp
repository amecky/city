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

ActionTestState::ActionTestState(ds::Game* game) : ds::GameState("ActionTestState", game), _mesh(0) , _offset(0) {
	_ttl = 0.5f;
	_scene = ds::res::getScene("TestObjects");
	game->addScene("ActionTest", _scene);
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
	_camera = graphics::getFPSCamera();
	_camera->setPosition(v3(0, 0, -0.5), v3(0.0f, 0.0f, 0.0f));
	//_camera->resetPitch(DEGTORAD(25.0f));
	//_scene = ds::res::getScene("TestObjects");
	_mesh = new ds::Mesh();

	_material = ds::res::find("TexturedMeshMaterial", ds::ResourceType::MATERIAL);
	// build squares to show vertices of the selected face
	float dx = 0.0625f * 0.5f;
	float dy = (64.0f / 768.0f) * 0.5f;
	v3 p[] = { v3(-dx, dy, 0.0f), v3(dx, dy, 0.0f), v3(dx, -dy, 0.0f), v3(-dx, -dy, 0.0f) };
	ds::gen::MeshGen g;
	//g.add_cube(v3(0, 0, 0), v3(2,2,2));
	//g.debug_colors();
	g.add_face(p);
	g.texture_face(0, math::buildTexture(650, 260, 64, 64));
	g.build(_mesh);
	_id = _scene->add(_mesh, v3(0, 0, 0), _material);
}

void ActionTestState::activate() {
	_camera->setPosition(v3(0, 0, -4), v3(0.0f, 0.0f, 0.0f));
	//_camera->setPosition(v3(0, 3, -6), v3(0.0f, 0.0f, 0.1f));
	//_camera->resetPitch(DEGTORAD(25.0f));
	_camera->resetYaw(0.0f);
	_scene->setActive(true);
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
	//_scene->draw();
	drawGUI();
}

void ActionTestState::drawGUI() {
	v2 pos(10, 760);
	int state = 1;
	gui::start(1, &pos, true);
	gui::begin("Editor", &state);
	gui::InputFloat("TTL", &_ttl);
	if (gui::Button("Rotate_180")) {
		_scene->rotateTo(_id, v3(0, 0, 0), v3(0.0f, 0.0f, HALF_PI),_ttl);
	}
	gui::end();
	
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

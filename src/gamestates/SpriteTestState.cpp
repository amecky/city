#include "SpriteTestState.h"
#include <utils\Log.h>
#include <base\EventStream.h>
#include <base\InputSystem.h>
#include <gen\MeshGen.h>
#include <gen\MeshGenCommand.h>
#include <utils\ObjLoader.h>
#include <renderer\graphics.h>
#include <utils\TileMapReader.h>
#include <utils\FileUtils.h>

SpriteTestState::SpriteTestState(ds::Game* game) : ds::GameState("SpriteTestState", game) {
	_scene = game->create2DScene("Sprites");
	_material = ds::res::find("SpriteMaterial", ds::ResourceType::MATERIAL);
	ds::Material* m = ds::res::getMaterial(_material);
	m->texture = ds::res::find("TextureArray", ds::ResourceType::TEXTURE);
	_first = _scene->add(v2(640, 480), math::buildTexture(650, 260, 64, 64), _material);
	_scene->add(v2(320, 480), math::buildTexture(650, 260, 64, 64), _material);
	_scene->setActive(true);
}


SpriteTestState::~SpriteTestState() {
}

// -------------------------------------------------------
// init
// -------------------------------------------------------
void SpriteTestState::init() {	
	
}

void SpriteTestState::activate() {	
}
// -------------------------------------------------------
// update
// -------------------------------------------------------
int SpriteTestState::update(float dt) {	
	return 0;
}

// -------------------------------------------------------
// render
// -------------------------------------------------------
void SpriteTestState::render() {
}

// -------------------------------------------------------
// onChar
// -------------------------------------------------------
int SpriteTestState::onChar(int ascii) {	
	if (ascii == '1') {
		_scene->scaleTo(_first, v2(1, 1), v2(0.5f, 0.5f), 1.0f);
	}
	return 0;
}

#include "City.h"
#include "utils\Log.h"
#include <gamestates\GameStateMachine.h>
#include "gamestates\GeoTestState.h"
#include "gamestates\MeshGenTestState.h"
#include "gamestates\WorldState.h"
#include "gamestates\ActionTestState.h"
#include "gamestates\SpriteTestState.h"

ds::BaseApp *app = new City(); 

City::City() : ds::BaseApp() {
}

City::~City() {
}

// -------------------------------------------------------
// Load content and prepare game
// -------------------------------------------------------
bool City::loadContent() {	
	addGameState(new GeoTestState(game));
	addGameState(new MeshGenTestState("house_3", game));
	addGameState(new WorldState(game));
	addGameState(new ActionTestState(game));
	addGameState(new SpriteTestState(game));
	connectGameStates("MeshGenTestState", 1, "WorldState");
	connectGameStates("WorldState", 1, "MeshGenTestState");
	return true;
}

void City::init() {
	// for testing
	//activate("MeshGenTestState");
	activate("SpriteTestState");
	//activate("WorldState");
}

void City::render() {
}

void City::OnChar(uint8_t ascii) {
	
}
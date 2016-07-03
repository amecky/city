#include "City.h"
#include "utils\Log.h"
#include <gamestates\GameStateMachine.h>
#include "gamestates\GeoTestState.h"
#include "gamestates\MeshGenTestState.h"
#include "gamestates\WorldState.h"
#include "gamestates\ActionTestState.h"
ds::BaseApp *app = new City(); 

City::City() : ds::BaseApp() {
}

City::~City() {
}

// -------------------------------------------------------
// Load content and prepare game
// -------------------------------------------------------
bool City::loadContent() {	
	addGameState(new GeoTestState());
	addGameState(new MeshGenTestState("house_3"));
	addGameState(new WorldState());
	addGameState(new ActionTestState());
	connectGameStates("MeshGenTestState", 1, "WorldState");
	connectGameStates("WorldState", 1, "MeshGenTestState");
	return true;
}

void City::init() {
	// for testing
	//activate("MeshGenTestState");
	activate("ActionTestState");
	//activate("WorldState");
}

void City::render() {
}

void City::OnChar(uint8_t ascii) {
	
}
#pragma comment(lib, "D11.lib")
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dsound.lib")
#pragma comment(lib, "dxerr.lib")
#pragma warning(disable : 4995)

#pragma once
#include "base\BaseApp.h"
#include <renderer\render_types.h>

class City : public ds::BaseApp {

public:	
	City();
	virtual ~City();
	bool initialize() {
		return true;
	}
	bool loadContent();
	const char* getTitle() {
		return "City";
	}
	void init();
	void update(float dt) {}
	void render();
protected:
	void OnChar(uint8_t ascii);
private:
	ds::SpriteBuffer* _sprites;
};
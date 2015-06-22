#ifndef INPUT_DEVICE_H
#define INPUT_DEVICE_H

#include "Definitions.h"

#include <SDL.h>
#include <iostream>
#include <map>

class InputDevice {
public:
	bool initialize();
	void update(SDL_Event* event);
	bool getEvent(GAME_EVENT);
	int getX();
	int getY();
private:
	std::map<GAME_EVENT, bool> currentEvents;
	int mouseX;
	int mouseY;
};
#endif
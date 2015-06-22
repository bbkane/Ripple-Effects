#ifndef VIEW_H
#define VIEW_H

#include "Definitions.h"
#include "InputDevice.h"

#include <iostream>

class View {
public:
	bool initialize(InputDevice* iDevice, GAME_FLT x, GAME_FLT y);
	void update();
	GAME_FLT getX() const;
	GAME_FLT getY() const;
private:
	InputDevice* iDevice;
	GAME_FLT x;
	GAME_FLT y;
};
#endif
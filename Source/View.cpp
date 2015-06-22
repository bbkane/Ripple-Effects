#include "View.h"

bool View::initialize(InputDevice* iDevice, GAME_FLT x, GAME_FLT y) {
	this->x = x;
	this->y = y;
	this->iDevice = iDevice;
	return true;
}

void View::update() {
	//might want to update view at some time
}

GAME_FLT View::getX() const {
	return this->x;
}

GAME_FLT View::getY() const {
	return this->y;
}
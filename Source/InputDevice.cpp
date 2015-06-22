#include "InputDevice.h"

bool InputDevice::initialize() {
	this->currentEvents[LEFT_MOUSE_DOWN] = false;
	this->currentEvents[RIGHT_MOUSE_DOWN] = false;
	return true;
}

void InputDevice::update(SDL_Event* event) {
	if(event->type == SDL_MOUSEBUTTONDOWN) {
		if(event->button.button == SDL_BUTTON_LEFT) {
			this->currentEvents[LEFT_MOUSE_DOWN] = true;
		} else if(event->button.button == SDL_BUTTON_RIGHT) {
			this->currentEvents[RIGHT_MOUSE_DOWN] = true;
		}
	} else {
		this->currentEvents[LEFT_MOUSE_DOWN] = false;
		this->currentEvents[RIGHT_MOUSE_DOWN] = false;
	}
	if(event->type == SDL_MOUSEMOTION) {
		this->mouseX = event->motion.x;
		this->mouseY = event->motion.y;
	}
}

bool InputDevice::getEvent(GAME_EVENT event) {
	return this->currentEvents[event];
}

int InputDevice::getX() {return mouseX;}

int InputDevice::getY() {return mouseY;}
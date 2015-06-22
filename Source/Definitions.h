/*
* Author:	Keith Bush
*			UALR
* 
* Date:		February 24, 2015 (Completed)
*
* File:		Definitions.h (Hmwk.1.Solution)
*
* Purpose:	This is a standard type redefinitions header that allows
*           for flexibility in programming should design parameters change.
*           Ideally, every SDL2 specific type would be renamed allowing
*           the code to be decoupled from any specific Media Library.
*/

#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <string>

//Basic Types
typedef unsigned int	Uint32;
typedef float			GAME_FLT;
typedef Uint32			GAME_INT;


typedef struct GamePhysics {
	GAME_FLT density;
	GAME_FLT restitution;
	GAME_FLT angularDamping;
	GAME_FLT linearDamping;
	GAME_FLT angularForce;
	GAME_FLT linearForce;
	GAME_FLT friction;
	std::string type;
	std::string shape;
} GamePhysics;

typedef struct ActorInfo {
	std::string name;
	GAME_FLT x;
	GAME_FLT y;
	GAME_FLT angle;
} ActorInfo;


//Event Types
//enum GAME_EVENT {GAME_UP,GAME_DOWN,GAME_LEFT,GAME_RIGHT, GAME_ACTION, GAME_ALT_UP, GAME_ALT_DOWN, GAME_ALT_LEFT, GAME_ALT_RIGHT};
enum GAME_EVENT {LEFT_MOUSE_DOWN, RIGHT_MOUSE_DOWN};
//Constants
const GAME_FLT PI = 3.14159f;

enum COLLISION_TYPES {BARREL, DOCK, ROCK};

//========================================
//Base Game Constants
//========================================
const GAME_INT SCREEN_WIDTH = 800;
const GAME_INT SCREEN_HEIGHT = 600;
const GAME_INT GAME_FPS = 100;

const float fPRV = 10.0f;

inline float PW2RW(float x){return x*fPRV;}

inline float RW2PW(float x){return x/fPRV;}

inline float RW2PW(int x){return (float)x/fPRV;}

inline float RW2PWAngle(float x){return((float)x*(2.0f*3.14159f)/360.0f);} //degrees to radians

inline float PW2RWAngle(float x){return((float)x*360.0f/(2.0f*3.14159f));} //radians to degrees

#endif

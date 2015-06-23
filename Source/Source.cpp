/*
* Author:	Benjamin Kane
*			UALR
* 
* Date:		May ?, 2015	
*
* File:		Source.cpp
*
* Purpose:	A game
* Video:	https://www.youtube.com/watch?v=PbtR768IPqU
*/

#include <memory>
#include <iostream>
#include "SDL.h"
#include "GraphicsDevice.h"
#include "Timer.h"
#include "Actor.h"
#include "Definitions.h"
#include "Box2D/Box2D.h"

#include "ArtAssetLibrary.h"
#include "InputDevice.h"
#include "Definitions.h"
#include "Game.h"
#include "SDL_mixer.h"

#include <fstream>

int main(int argc, char *argv[])
{
	std::ofstream fout("Current-Directory-HERE!!!.txt");
	fout << "hi" << std::endl;
	fout.close();

	//Construct Graphical Device
	GraphicsDevice* gDevice = new GraphicsDevice(SCREEN_WIDTH, SCREEN_HEIGHT);
	if(!gDevice->Initialize(false))
	{
		printf( "Graphics Device could not initialize! SDL_Error: %s\n", SDL_GetError() );
		exit(1);
	}

	//Construct Event in loop
	SDL_Event* event = new SDL_Event();
	if(!event){
		printf( "SDL Event could not initialize! SDL_Error: %s\n", SDL_GetError() );
		exit(1);
	}

	//========================================
	//Construct Input Device
	//========================================
	InputDevice* iDevice = new InputDevice();
	if(!iDevice->initialize())
	{
		printf( "Input Device could not initialize!");
		exit(1);
	}

    //Load the Mixer subsystem
	if(Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096 ) <0)
	{
		printf( "SDL Mixer could not initialize! SDL_Error: %s\n", Mix_GetError() );
		exit(1);	    		
	}

    //Allocate sufficient channels
    Mix_AllocateChannels(100);

	Mix_Music *music = Mix_LoadMUS( "./Assets/Sounds/8-bit-music.mp3" );
	Mix_PlayMusic(music, -1);

    //----------------------------------------------
    // END MIXER INIT 
    //----------------------------------------------

	//Create and load game
	std::string level = "./Config/level3.xml";
	Game* game = new Game();
	game->initialize(gDevice, iDevice, 100); //TODO: needs to be 100, changing for rock-creating Purpusoes
	game->loadLevel(level);

	//========================================
	//Main Game Loop
	//========================================
	bool quit = false;

	//While the user hasn't quit
	while(!quit)
	{

		//Check for Event
		if(SDL_PollEvent(event))
		{
			if(event->type == SDL_QUIT)
			{
				quit = true;
			}

			//Update the Input Device with the Event
			iDevice->update(event);
		}

		//Execute the Game (update and draw a frame)
		game->run();

	}
	game->destroy();
	delete game;

	return 0;

}

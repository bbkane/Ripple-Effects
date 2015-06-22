#ifndef MUSIC_ASSET_LIBRARY
#define MUSIC_ASSET_LIBRARY

#include <SDL_mixer.h>
#include <map>
#include <string>

class MusicAssetLibrary {
public:

	bool destroy();
	bool initialize();
	Mix_Chunk* search(std::string);
private:
	std::map<std::string, Mix_Chunk*> library;
};

#endif
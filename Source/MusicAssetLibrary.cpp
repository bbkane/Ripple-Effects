#include "MusicAssetLibrary.h"

bool MusicAssetLibrary::initialize() {
	library["scratch"] = Mix_LoadWAV("./Assets/Sounds/scratch.wav");
	library["high"] = Mix_LoadWAV("./Assets/Sounds/high.wav");
	library["splash"]= Mix_LoadWAV("./Assets/Sounds/waterSPLASH.WAV");
	library["clunk"] = Mix_LoadWAV("./Assets/Sounds/clunk.wav");
	library["crash"] = Mix_LoadWAV("./Assets/Sounds/crash.wav");
	return true;
}

bool MusicAssetLibrary::destroy() {
	for(auto i: library) {
		Mix_FreeChunk(i.second);
	}
	return true;
}

Mix_Chunk* MusicAssetLibrary::search(std::string name) {
	return library[name];
}

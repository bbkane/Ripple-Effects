#ifndef ART_ASSET_LIBRARY_H
#define ART_ASSET_LIBRARY_H

#include "GraphicsDevice.h"
#include "Texture.h"

#include <map>
#include <string>
#include <iostream>

class ArtAssetLibrary {
public:
	ArtAssetLibrary();
	bool initialize(GraphicsDevice* gDevice);
	bool destroy();
	Texture* search(std::string name);
private:
	std::map<std::string, Texture*> library;
	GraphicsDevice* gDevice;
	Texture* bulletTexture;
	Texture* carrierTexture;
	Texture* barrelTexture;
	Texture* playerTexture;
	Texture* rockTexture;
	Texture* skullTexture;
	Texture* tankTexture;
	Texture* treeTexture;
	Texture* turretTexture;
	Texture* spaceShipTexture;
	Texture* dockTexture;

};

#endif
#include "ArtAssetLibrary.h"

ArtAssetLibrary::ArtAssetLibrary() {
	this->barrelTexture = nullptr;
}

//I don't need most of these textures but I might someday

bool ArtAssetLibrary::initialize(GraphicsDevice* gDevice) {
	this->gDevice = gDevice;
	//build textures
	this->bulletTexture = new Texture();
	bulletTexture->load(gDevice->GetRenderer(), "./Assets/Images/t_bullet.png");
	library["Bullet"] = bulletTexture;

	this->dockTexture = new Texture();
	dockTexture->load(gDevice->GetRenderer(), "./Assets/Images/dock.png");
	library["Dock"]  = dockTexture;

	this->carrierTexture = new Texture();
	carrierTexture->load(gDevice->GetRenderer(), "./Assets/Images/t_carrier.png");
	library["Carrier"] = carrierTexture;

	this->barrelTexture = new Texture();
	barrelTexture->load(gDevice->GetRenderer(), "./Assets/Images/barrel.png");
	library["Barrel"] = barrelTexture;

	this->playerTexture = new Texture();
	playerTexture->load(gDevice->GetRenderer(), "./Assets/Images/t_player.png");
	library["Player"] = playerTexture;

	this->rockTexture = new Texture();
	rockTexture->load(gDevice->GetRenderer(), "./Assets/Images/t_rock.png");
	library["Rock"] = rockTexture;

	this->skullTexture = new Texture();
	skullTexture->load(gDevice->GetRenderer(), "./Assets/Images/t_skull.png");
	library["Skull"] = skullTexture;

	this->tankTexture = new Texture();
	tankTexture->load(gDevice->GetRenderer(), "./Assets/Images/t_tank.png");
	library["Tank"] = tankTexture;

	this->treeTexture = new Texture();
	treeTexture->load(gDevice->GetRenderer(), "./Assets/Images/t_tree.png");
	library["Tree"] = treeTexture;

	this->turretTexture = new Texture();
	turretTexture->load(gDevice->GetRenderer(), "./Assets/Images/t_turret.png");
	library["Turret"] = turretTexture;

	this ->spaceShipTexture = new Texture();
	spaceShipTexture->load(gDevice->GetRenderer(), "./Assets/Images/PlayerPaper.png");
	library["SpaceShip"] = spaceShipTexture;

	return true;
}

Texture* ArtAssetLibrary::search(std::string name) {
	if(library.count(name)) {
		return library[name];
	}
	else {
		std::cerr << "Texture " << name << " not found" << std::endl;
		return nullptr;
	}
}

bool ArtAssetLibrary::destroy() {
	this->carrierTexture->free();
	delete this->carrierTexture;
	this->barrelTexture->free();
	delete this->barrelTexture;
	return true;
}
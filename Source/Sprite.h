#ifndef SPRITE_H
#define SPRITE_H

#include"Component.h"
class Actor;
class GraphicsDevice;
class Texture;
class View;

class Sprite : public Component
{
public:
	Sprite(std::shared_ptr<Actor>);
	~Sprite();
	void Initialize(GraphicsDevice*, Texture*, View*);
	void Start();
	void Update();
	void Finish();
	void Draw();
	void Present();
	bool GetIsAlive();
protected:
	Texture* texture;
	GraphicsDevice* gDevice;
	View* view;
	bool isAlive;
};


#endif
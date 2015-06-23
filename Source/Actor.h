#ifndef Actor_H
#define Actor_H

#include <memory>
#include <iostream>
#include <vector>
#include "Box2D/Box2D.h"
#include "Texture.h"
#include <string>

class Component;
class GraphicsDevice;
class Game;

class Actor : public std::enable_shared_from_this<Actor>
{
public:
	Actor();
	~Actor();
	bool Initialize(Game* game, std::string name, float x, float y, float angle);
	void AddComponent(std::shared_ptr<Component> component);
	bool GetIsAlive();
	void SetIsAlive(bool alive);
	template<class T>
	std::shared_ptr<T> GetComponent()
	{
		for(auto comp : components)
		{
			std::shared_ptr<T> target;
			if((target = std::dynamic_pointer_cast<T>(comp)))
			{
				return(target);
			}
		}
	
		//Return NULL;
		return(std::shared_ptr<T>());
	}



	void Update();
	std::string GetName();
protected:
	
	std::vector<std::shared_ptr<Component>> components;
    bool initialized;
	bool isAlive;
	std::string name;
};

#endif

#include"Definitions.h"
#include"BarrelBehavior.h"
#include"RigidBody.h"
#include <iostream>
#include <Box2D\Common\b2Math.h>
#include <SDL_mixer.h>
#include "MusicAssetLibrary.h"

//put lifetime info in behaviors. 

BarrelBehavior::BarrelBehavior(std::shared_ptr<Actor> owner) : Component(owner){}

BarrelBehavior::~BarrelBehavior(){}

void BarrelBehavior::Initialize(std::vector<b2Vec2>* leftBank, std::vector<b2Vec2>* rightBank,MusicAssetLibrary* mLibrary,GAME_INT *score,float dt)
{
	this->dt = dt;
	this->leftBank = leftBank;
	this->rightBank = rightBank;
	this->timeLived = b2Timer();
	this->touchingDock = 0;
	this->touchingRock = 0;
	this->score = score;
	this->mLibrary = mLibrary;
}

void BarrelBehavior::Start(){}

void BarrelBehavior::Update()
{

	b2Body *body =_owner->GetComponent<RigidBody>()->GetBody();

	//Is the barrel dead?
	if(touchingDock) {
		(*score)++; //increase score
		Mix_PlayChannel( -1,mLibrary->search("clunk"),0 );
		_owner->SetIsAlive(false);
	}

	if(touchingRock) {
		if(*score > 0) {
			(*score)--;
		}
		Mix_PlayChannel( -1,mLibrary->search("crash"),0 );
		_owner->SetIsAlive(false);
	}

	//get segment of river
	std::pair<b2Vec2,b2Vec2>l;
	std::pair<b2Vec2,b2Vec2>r;
	for(auto i = leftBank->begin(), j = rightBank->begin(); (i+1) != leftBank->end(),(j+1)!=rightBank->end();i++,j++) {
		//search on the left  y coordinates to see which segment the barrel is in | b /
		if (body->GetPosition().y > i->y && body->GetPosition().y < (i+1)->y) {//Only checking on i side- only valid if boundaries are horizontal TODO: make better
			l = std::make_pair(*i, *(i+1));
			r = std::make_pair(*j, *(j+1));
			break; //done with loop
		}
	}
	//std::cerr << "Body in -----------" << std::endl;
	//std::cerr << (l.first.x) << ' ' << (l.first.y) << " and " << (l.second.x) << " " << (l.second.y) << std::endl;
	//std::cerr << (r.first.x) << ' ' << (r.first.y) << " and " << (r.second.x) << " " << (r.second.y) << std::endl;
	//std::cerr << "End Body in ------" << std::endl;

	//levels must have nearly horizontal choke points and there cannot be parallel lines

	//equation of a line in matrix from from four points (two from each line)
	//-dy x + dx y = -dy x1 + dx y1

	//figure out point to aim at
	//get deltas between points
	float deltaLY = l.second.y - l.first.y;
	float deltaLX = l.second.x - l.first.x;
	float deltaRY = r.second.y - r.first.y;
	float deltaRX = r.second.x - r.first.x;

	//error if one of these is zero (parallel lines) Test this.......
	if(deltaLX * deltaRX  == 0.0f) {
		//std::cerr<< __FUNCTION__ << "Parallel lines not allowed in level" << std::endl;
		//it doesn't seem to be hurting much...
	}
	//turn into ax + by = c equation of line for matrices
	//The Ax part
	b2Mat22 linesMatrix(deltaLY, -deltaLX, deltaRY, -deltaRX); //row vectors 11, 12, 21, 22
	//the b part
	b2Vec2	linesVector = b2Vec2(deltaLY*l.first.x - deltaLX * l.first.y, deltaRY * r.first.x - deltaRX * r.first.y);
	//std::cout << "linesVector = " << linesVector.x << " " << linesVector.y << std::endl;
	//get the intersection
	b2Vec2 intersection = linesMatrix.Solve(linesVector); 
	//std::cout << " intersection : x: " << (intersection.x) << " y: " << (intersection.y) << std::endl;
	//scale vector by where barrel is
	b2Vec2 force = intersection - body->GetPosition();

	//make sure it flows downward
	if (intersection.y < body->GetPosition().y) {
		force = -force;
	}

	//scale force by the square of the length of the vector (which is proportional to the width of the channel)
	const float scale = 800; //scaling factor
	force.x = force.x / force.LengthSquared() * scale;
	force.y = force.y / force.LengthSquared() * scale;
	
	body->ApplyForceToCenter(force,true);
}

void BarrelBehavior::StartTouchingRock() 
{
	touchingRock++;
}

void BarrelBehavior::StartTouchingDock() {
	touchingDock++;
}
void BarrelBehavior::Finish(){}

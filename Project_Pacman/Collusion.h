#pragma once
#include "Pacman.h"
#include "SmartDemon.h"
#include "Cookie.h"


class Collusion
{
public:
	// check Pacman & Ghost Collusion 
	bool isPacmanCollidedGhost(Pacman & pacman, Demon * demon);
	// check Pacman & Cookie Collusion
	bool isPacmanCollidedCookie(Pacman & pacman, StaticObject * cookie);
	// check Wall | Cookie & Ghost|Pacman Collusion
	bool CheckCollusion(StaticObject * obj, const Character * charcter);
	// engine of Collusion
	bool AABBCollision(const sf::FloatRect& obj1, const sf::FloatRect& currOBJ);
};


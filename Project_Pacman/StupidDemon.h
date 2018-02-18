#pragma once
#include "Demon.h"
#include "Character.h"

class StupidDemon :public Demon
{
public:
	StupidDemon(const sf::Vector2f & _pos, sf::Color _color);
	void move(); // move the Ghost
};


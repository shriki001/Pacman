#pragma once
#include "StaticObject.h"

class Wall : public StaticObject
{

public:

	Wall(const sf::Vector2f & _pos, 
		 sf::Color _color = sf::Color::Transparent);
	void draw(sf::RenderWindow&)const;     // draw object on window
	sf::Vector2f getPosition() const;         // return object position
	sf::Color getColor();               // return object color
	sf::Vector2f getCenter() const; // return object center
};


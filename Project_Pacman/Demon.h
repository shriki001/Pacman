#pragma once
#include "Character.h"

class Demon :public Character
{
public:
	Demon(const sf::Vector2f & _pos = {0,0},
		 const sf::Color _color = sf::Color::Transparent);
	virtual void move() = 0;                  // Move of the Demons
	virtual void draw(sf::RenderWindow&) const; // draw the Demons 

protected:
	sf::Texture m_texture;
};


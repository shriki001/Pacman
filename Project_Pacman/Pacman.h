#pragma once
#include "Character.h"

class Pacman : public Character
{
public:
	Pacman(const sf::Vector2f & _pos = { 0.f,0.f },
		  sf::Color _color = sf::Color::Transparent);
	void draw(sf::RenderWindow&) const;			//draw Pacman in window
	void move();								// move Pacman in grid

private:
	sf::Texture m_texture;
	sf::Texture m_textureUp;
	sf::Texture m_textureDown;
	
};


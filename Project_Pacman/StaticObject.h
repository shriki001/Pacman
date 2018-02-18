#pragma once
#include <SFML/Graphics.hpp>
#include "Settings.h"

class StaticObject
{
public:
	virtual void draw(sf::RenderWindow&)const = 0; // draw object on the window
	virtual sf::Vector2f getCenter() const = 0;// get object center
	virtual sf::Vector2f getPosition() const=0; // get object position
	sf::Color getColor() const; // get object color
	sf::Sprite getObject() const; // return object 

protected:
	sf::Sprite m_body;
	sf::Texture m_texture;
	sf::Color m_color;

};


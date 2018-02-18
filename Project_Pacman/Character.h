#pragma once
#include <SFML/Graphics.hpp>
#include "Settings.h"
class Character 
{
public:
	virtual void draw(sf::RenderWindow&)const = 0; // draw the character
	virtual void move() = 0;				 // move the character (Virtual)
	void setPosition(sf::Vector2f pos);		 // set character position
	void setColor(sf::Color color);			 // set character color
	void setState(PlayerState state);		 // set character direction
	PlayerState getDirection();				 // get character direction
	float getSpeed() const;					 // get character speed
	sf::Sprite getObject() const;			 // get character Object
	void setSpeed(float speed);				 // set character speed
	sf::Vector2f getPosition() const;		// get character position
	sf::Vector2f getCenter();				// get character center

protected:
	float m_speed;
	sf::Sprite m_body;
	sf::Color m_color;
	enum PlayerState m_key;
};


#include "Character.h"


//---------------------------------------------------------------------------//
/*
 * This method returns the speed of the charcter in pixels/second
 */
float Character::getSpeed() const
{
	return m_speed;
}

//---------------------------------------------------------------------------//
/*
 *
 */
sf::Sprite Character::getObject() const
{
	return m_body;
}

//---------------------------------------------------------------------------//
/*
 * This method get a float number as new speed (pixels/second)
 * sets the new speed of the character
 */
void Character::setSpeed(float speed)
{
	m_speed = speed;
}

//---------------------------------------------------------------------------//
/* 
 *  This returns the position (top-left corner) of the charcter
 */
sf::Vector2f Character::getPosition() const
{
	return m_body.getPosition();
}

//---------------------------------------------------------------------------//
/*
 * This returns the center point of the character's place
 */
sf::Vector2f Character::getCenter()
{
	sf::Vector2f center;
	center.x = getPosition().x + SIZE1 / 2;
	center.y = getPosition().y + SIZE1 / 2;
	return center;
}

//---------------------------------------------------------------------------//
/*
 * This method get a float vector as new position (top-left corner)
 * sets the new position of the character
 */
void Character::setPosition(sf::Vector2f pos)
{
	m_body.setPosition(pos);
}

//---------------------------------------------------------------------------//
/*
 * This method get a color as new color of the charcater
 * sets the new color of the character
 */
void Character::setColor(sf::Color color)
{
	m_color = color;
}

//---------------------------------------------------------------------------//
/*
 * This method get a State as new direction
 * sets the new direction of the character
 */
void Character::setState(PlayerState state)
{
	m_key = state;
}

//---------------------------------------------------------------------------//
/*
 * This method returns the move direction of the character
 */
PlayerState Character::getDirection()
{
	return m_key;
}

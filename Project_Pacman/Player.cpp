#include "Player.h"

Player::Player()
{
	//m_character = new Character;
}

Player::~Player()
{
	//	delete m_character;
}

//---------------------------------------------------------------------------//
/*
 *
 */
void Player::draw(sf::RenderWindow & app) const
{
	m_character->draw(app);
}

//---------------------------------------------------------------------------//
/*
 *
 */
void Player::playMove(PlayerState last)
{
	m_character->setState(last);
	m_character->move();
}


//---------------------------------------------------------------------------//
/*
 *
 */
PlayerState Player::getNew()
{
	return m_newD;
}

//---------------------------------------------------------------------------//
/*
 *
 */
void Player::setStayDirect(PlayerState state)
{
	m_newD = state;
}

//---------------------------------------------------------------------------//
/*
 *
 */
Character * Player::getObject() const
{
	return m_character;
}

//---------------------------------------------------------------------------//
/*
 *
 */
PlayerState Player::getDirection() const
{
	return m_character->getDirection();
}

//---------------------------------------------------------------------------//
/*
 *
 */
sf::Vector2f Player::getCenter() const
{
	sf::Vector2f center;
	center.x = getPosition().x + SIZE1 / 2;
	center.y = (getPosition().y - 2 * SIZE1) + SIZE1 / 2;
	return center;
}

//---------------------------------------------------------------------------//
/*
 *
 */
void Player::setOrigin(sf::Vector2f newPos)
{
	m_character->getObject().setOrigin(newPos);
}

//---------------------------------------------------------------------------//
/*
 *
 */
sf::Vector2f Player::getPosition() const
{
	return m_character->getPosition();
}

//---------------------------------------------------------------------------//
/*
 *
 */
void Player::setPosition(float x, float y)
{
	sf::Vector2f newPos = { x,y };
	m_character->setPosition(newPos);
}

//---------------------------------------------------------------------------//
/*
 *
 */
void Player::setPosition(sf::Vector2f newPlace)
{
	m_character->setPosition(newPlace);
}

//---------------------------------------------------------------------------//
/*
 *
 */
float Player::getSpeed() const
{
	return m_character->getSpeed();
}

//---------------------------------------------------------------------------//
/*
 *
 */
void Player::setSpeed(float speed)
{
	m_character->setSpeed(speed);
}

//---------------------------------------------------------------------------//
/*
 *
 */
void Player::setPlayer(sf::Vector2f newPos, sf::Color newColor)
{
	m_character->setPosition(newPos);
	m_character->setColor(newColor);
}

#include "PlayerP.h"

//---------------------------------------------------------------------------//
/*
 *
 */
PlayerP::PlayerP(sf::Vector2f newPos, sf::Color newColor)
	:m_life(LIFE)
{
	m_character = new Pacman(sf::Vector2f(0, 0), sf::Color::Transparent);
	m_character->setPosition(newPos);
	m_character->setColor(newColor);
}

//---------------------------------------------------------------------------//
/*
 *
 */
PlayerP::~PlayerP()
{
	delete m_character;
}

//---------------------------------------------------------------------------//
/*
 *
 */
PlayerState PlayerP::setNewDirect(PlayerState last)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		m_newD = RIGHT_T;

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		switch (last)
		{
		case LEFT_T:
			m_newD = STAYLEFT_T;
			break;
		case RIGHT_T:
			m_newD = STAY_T;
			break;
		case UP_T:
			m_newD = STAYUP_T;
			break;
		case DOWN_T:
			m_newD = STAYDOWN_T;
			break;
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		m_newD = LEFT_T;

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		m_newD = UP_T;

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		m_newD = DOWN_T;
	return m_newD;
}

//---------------------------------------------------------------------------//
/*
 *
 */
void PlayerP::kill()
{
	m_life--;
	m_character->setState(STAY_T);
	setStayDirect(STAY_T);
}

//---------------------------------------------------------------------------//
/*
 *
 */
bool PlayerP::isAlive() const
{
	return m_life > 0;
}

//---------------------------------------------------------------------------//
/*
 *
 */
size_t PlayerP::getlives() const
{
	return m_life;
}

//---------------------------------------------------------------------------//
/*
 *
 */
void PlayerP::addLife()
{
	m_life++;
}

//---------------------------------------------------------------------------//
/*
 *
 */
Pacman * PlayerP::getObject() const
{
	return dynamic_cast<Pacman*>(m_character);
}

void PlayerP::setlife(size_t x)
{
	m_life = x;
}

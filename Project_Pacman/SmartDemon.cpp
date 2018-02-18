#include "SmartDemon.h"


//---------------------------------------------------------------------------//
/*
 * Constructor of the Smart demon object in the game, defines his 
 * initial settings as speed , direction and animation
 */
SmartDemon::SmartDemon(const sf::Vector2f & _pos, sf::Color _color)
{
	m_color = _color;
	m_key = LEFT_T;
	m_texture.loadFromFile("Image\\demon.png");
	m_body.setTexture(m_texture);
	m_body.setColor(m_color);
	m_body.setPosition(_pos);
}
//---------------------------------------------------------------------------//
/*
 * 

*/
void SmartDemon::SmartMove(PlayerState dir)
{
	switch (dir)
	{
	case LEFT_T:
		m_key = RIGHT_T;
		break;
	case RIGHT_T:
		m_key = LEFT_T;
		break;
	case UP_T:
		m_key = DOWN_T;
		break;
	case DOWN_T:
		m_key = UP_T;
		break;
	}

}
//---------------------------------------------------------------------------//
/*
 *  This method defines the movement of the Smart demon on screen
 */
void SmartDemon::move()
{
	srand((unsigned) time(NULL));
	if (rand() % 50 < 10)
		m_speed = 1.5;
	else
		m_speed = 1;
	sf::Vector2f update;
	switch (m_key)
	{
	case RIGHT_T:
		update = sf::Vector2f(m_speed, 0.f);
		break;
	case LEFT_T:
		update = sf::Vector2f(-m_speed, 0.f);
		break;
	case UP_T:
		update = sf::Vector2f(0.f, -m_speed);
		break;
	case DOWN_T:
		update = sf::Vector2f(0.f, m_speed);
		break;
	case STAY_T:
	case STAYUP_T:
	case STAYDOWN_T:
	case STAYLEFT_T:
		update = sf::Vector2f(0, 0);
		break;
	}
	sf::Vector2f currPos = m_body.getPosition();
	m_body.setPosition(currPos + update);
}

//---------------------------------------------------------------------------//
/*
 *  This method return the Manhaten Distance between 2 points 
 */
double SmartDemon::Manhaten(sf::Vector2f v1, sf::Vector2f v2)
{
	return std::abs(v1.x - v2.x) + std::abs(v1.y - v2.y);
}

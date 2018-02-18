#include "StupidDemon.h"


StupidDemon::StupidDemon(const sf::Vector2f & _pos, sf::Color _color)
{
	m_color = _color;
	m_key = RIGHT_T;
	m_texture.loadFromFile("Image\\demon.png");
	m_body.setTexture(m_texture);
	m_body.setColor(m_color);
	m_body.setPosition(_pos);
}

void StupidDemon::move()
{
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


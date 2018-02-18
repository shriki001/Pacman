#include "Demon.h"


//---------------------------------------------------------------------------//
/*
 * Constructor of the Demon object in the game, defines his initial settings
 * as speed , direction and animation
*/
Demon::Demon(const sf::Vector2f & _pos, const sf::Color _color) 
{
	m_color = _color;

	m_texture.loadFromFile("Image\\demon.png");
	m_body.setTexture(m_texture);
	m_body.setColor(m_color);
	m_body.setPosition(_pos);
}

//---------------------------------------------------------------------------//
/*
 *  This method gets a render window.
 *  draws the Demon on this window, according to his direction
 */
void Demon::draw(sf::RenderWindow & app) const
{
	sf::Sprite s1;
	s1.setColor(this->m_color);
	s1.setPosition(this->m_body.getPosition());
	s1.setTexture(m_texture);
	if ((time(nullptr) % 2) == 0)
	{
		s1.setColor(sf::Color(m_color.r, m_color.g-100, m_color.b));
	}
	else
		s1.setColor(sf::Color(m_color.r, m_color.g, m_color.b));

	if (m_key == RIGHT_T)
		s1.setTextureRect(sf::IntRect(SIZE1, 0, -SIZE1, SIZE1));
	else if (m_key == LEFT_T)
		s1.setTextureRect(sf::IntRect(0, 0, SIZE1, SIZE1));

	app.draw(s1);
}

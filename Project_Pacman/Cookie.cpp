#include "Cookie.h"

//---------------------------------------------------------------------------//
/*
 * Constructor of cookie
 */
Cookie::Cookie(const sf::Vector2f & _pos = {0,0},
	           const sf::Color &_color = sf::Color::Transparent)
{
	setCookieType(_color);
	m_color = _color;

	m_texture.loadFromFile("Image\\cookie.png");
	m_body.setTexture(m_texture);
	m_body.setColor(m_color);
	m_body.setPosition(_pos);
}

//---------------------------------------------------------------------------//
/*
 * This method gets a render window.
 * draws the cookie on this window
 */
void Cookie::draw(sf::RenderWindow& app)const
{
	sf::Sprite s1;
	s1.setColor(this->m_color);
	s1.setPosition(this->m_body.getPosition());
	s1.setTexture(m_texture);
	app.draw(s1);
}

//---------------------------------------------------------------------------//
/*
 * This method returns the type of the cookie (HEALTHY, NORMAL OR POISON)
 */
CookieType Cookie::getCookieType() const
{
	return m_type;
}

//---------------------------------------------------------------------------//
/*
 *  This method get a color and set it as the new type of object
 */
void Cookie::setCookieType(const sf::Color &_color)
{
	if (_color == sf::Color::Green)
		m_type = HEALTHY_T;
	else if (_color == sf::Color::Blue)
		m_type = POSION_T;
	else			// if color IS Red, or unkown
		m_type = NORMAL_T;
}

//---------------------------------------------------------------------------//
/*
 * This returns the center point of the cookie's place
 */
sf::Vector2f Cookie::getCenter() const
{
	sf::Vector2f center;
	center.x = getPosition().x + SIZE1 / 2;
	center.y = getPosition().y + SIZE1 / 2;
	return center;
}

//---------------------------------------------------------------------------//
/*
 *  This returns the position (top-left corner) of the cookie
 */
sf::Vector2f Cookie::getPosition() const
{
	return m_body.getPosition();
}


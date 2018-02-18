#include "Wall.h"

//---------------------------------------------------------------------------//
/*
 * Constructor of Wall object
 */
Wall::Wall(const sf::Vector2f & _pos, sf::Color _color )
{
	m_color = _color;
	m_texture.loadFromFile("Image\\wall.png");
	m_body.setTexture(m_texture);
	m_body.setColor(m_color);
	m_body.setPosition(_pos);
}

//---------------------------------------------------------------------------//
/*
 *  This method gets a render window.
 * draws the Wall on this window
 */
void Wall::draw(sf::RenderWindow& app)const
{
	sf::Sprite s1;
	s1.setColor(this->m_color);
	s1.setPosition(this->m_body.getPosition());
	s1.setTexture(m_texture);
	app.draw(s1);

}

//---------------------------------------------------------------------------//
/*
 *
 */
sf::Vector2f Wall::getPosition() const
{
	return m_body.getPosition();
}

//---------------------------------------------------------------------------//
/*
 *
 */
sf::Color Wall::getColor()
{
	return m_color;
}

//---------------------------------------------------------------------------//
/*
 *
 */
sf::Vector2f Wall::getCenter() const
{
	sf::Vector2f center;
	center.x = getPosition().x + SIZE1 / 2;
	center.y = getPosition().y + SIZE1 / 2;
	return center;
}
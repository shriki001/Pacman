
#include "StaticObject.h"

//---------------------------------------------------------------------------//
/*
 * return Static object color
 */
sf::Color StaticObject::getColor() const
{
	return m_color;
}

//---------------------------------------------------------------------------//
/*
 *  return Static object  body
 */
sf::Sprite StaticObject::getObject() const
{
	return m_body;
}


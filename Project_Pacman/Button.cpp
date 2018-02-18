#include "Button.h"


//---------------------------------------------------------------------------//
/*
 * Constuctor of Button
 */
Button::Button(unsigned x, unsigned y)
	:m_topLeft({ x,y }), m_name("a"), m_selected(false) {
	

}

//---------------------------------------------------------------------------//
/*
 *
 */
Button::Button(sf::Vector2u tl, int type, std::string name)
	:m_topLeft(tl), m_name(name) {



}
//---------------------------------------------------------------------------//
/*
 * This method gets a string, and rename the button to this string
 */
void Button::setName(std::string name)
{
	m_name = name;
}

//---------------------------------------------------------------------------//
/*
 *  This method gets a render window.
 *  draws the button name on this window, according to his position
 */
void Button::draw(sf::RenderWindow& app) const
{
	sf::Text _text;
	sf::Font _font;
	 _font.loadFromFile("font.ttf");
	_text.setFont(_font);
	_text.setPosition((sf::Vector2f)m_topLeft);
	_text.setString(m_name);
	_text.setOutlineColor(sf::Color::Black);
	_text.setCharacterSize(30);
	_text.setOutlineThickness(4);
	(m_selected) ? _text.setFillColor(SELECTED) :
		           _text.setFillColor(NOT_SELECTED);

	app.draw(_text);
}

//---------------------------------------------------------------------------//
/*
 *  This method set the button mode to be "Un-selected".
 */
void Button::select()
{
	m_selected = true;
}

//---------------------------------------------------------------------------//
/*
 *  This method set the button mode to be "Un-selected".
 */
void Button::unSelect()
{
	m_selected = false;
}

//---------------------------------------------------------------------------//
/*
 *  This method returns the position of the button on the screen.
 */
bool Button::isSelected() const
{
	return m_selected;
}

//---------------------------------------------------------------------------//
/*
 * This method returns the position of the button on the screen.
 * related to the top left corener of the rectangle bounds the button text
 */
sf::Vector2u Button::getPos() const
{
	return m_topLeft;
}

//---------------------------------------------------------------------------//
/*
 * This method sets the position of the button on the screen using 2 points
 * related to the top left corener of the rectangle bounds the button text
 */
void Button::setPos(unsigned x, unsigned y)
{
	m_topLeft = { x, y };
}

//---------------------------------------------------------------------------//
/*
* This method sets the position of the button on the screen using a vector
* related to the top left corener of the rectangle bounds the button text
*/
void Button::setPos(sf::Vector2u pos)
{
	m_topLeft = pos;
}
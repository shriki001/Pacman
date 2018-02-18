#pragma once

#include <SFML/Graphics.hpp>
#include "Settings.h"
#include <string>

class Button
{
public:
	Button(unsigned x = 0, unsigned y = 0);
	Button(sf::Vector2u tl, int type, std::string name);

	void setName(std::string name);          // set the name of the Button
	void draw(sf::RenderWindow& app) const; // draw the Button on the window
	void select();							// select Button
	void unSelect();						// unselected Button
	bool isSelected() const;				// check if Button is pressed 
	sf::Vector2u getPos() const;		   // return button place
	void setPos(unsigned x, unsigned y);   // set up  button place
	void setPos(sf::Vector2u pos);


private:
//	int m_type;					// code
	sf::Vector2u m_topLeft;		// top left corner where button exist
	std::string m_name;			// the name of the Button
	bool m_selected;			// flag if button is selected

	

};


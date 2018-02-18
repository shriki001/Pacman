#pragma once
#include "Menu.h"

class PauseMenu : public Menu
{
public:
	PauseMenu();
	ButtonDesc isSelected() const;           // return selected Button type 
	void draw(sf::RenderWindow & app) const; // draw Button on menu
	void update(sf::Vector2u size);          // update location of the a Button

private:
	sf::RectangleShape m_frame;
};
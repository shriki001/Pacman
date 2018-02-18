#pragma once
#include "Menu.h"

class StartMenu : public Menu
{
public:
	StartMenu();
	void update(sf::Vector2u size);     // update Button position
	ButtonDesc isSelected() const;      // return selected Button type 
	void draw(sf::RenderWindow& app) const; // draw Button on menu
	void briefWindow(sf::RenderWindow& window);   // show help window

private:
	sf::Sprite m_frame;
	sf::Texture m_frame_texture;

	sf::Sprite m_help;
	sf::Texture m_help_texture;

	sf::Text m_startMessage2;
	sf::Font m_font;

	void drawMsg2(sf::RenderWindow & window) const;
};


#pragma once
#include "Button_.h"
#include <SFML/Graphics.hpp>
#include <string>
#include "windows.h"

class EndGameMenu
{
public:
	EndGameMenu();

	void draw(sf::RenderWindow & app) const;
	std::string isSelected() const;
	void selectNext();
	void selectPrev();
	void run();
	void update(sf::Vector2u size);

private:
	Button m_new_game;
	Button m_exit;
	sf::Sprite m_frame;
	sf::Texture m_texture;
};

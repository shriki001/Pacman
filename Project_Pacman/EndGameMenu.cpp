#include "EndGameMenu.h"



EndGameMenu::EndGameMenu()
	:m_new_game(200, 300),
	m_exit(200, 420)
{
	m_texture.loadFromFile("Image\\bg.png");
	m_frame.setTexture(m_texture);
	m_new_game.select();
	m_new_game.setName("    Restart Game");
	m_exit.setName("    Exit Game");
}

void EndGameMenu::draw(sf::RenderWindow & app) const
{
	app.draw(m_frame);
	m_new_game.draw(app);
	m_exit.draw(app);

}

std::string EndGameMenu::isSelected() const
{
	if (m_new_game.isSelected())
		return "N";
	if (m_exit.isSelected())
		return "E";

	return "";
}

void EndGameMenu::selectNext()
{
	if (m_new_game.isSelected())
	{
		m_new_game.unSelect();
		m_exit.select();
	}

	else if (m_exit.isSelected())
	{
		m_exit.unSelect();
		m_new_game.select();
	}
	Sleep(200);
}

void EndGameMenu::selectPrev()
{
	if (m_new_game.isSelected())
	{
		m_new_game.unSelect();
		m_exit.select();
	}

	else if (m_exit.isSelected())
	{
		m_exit.unSelect();
		m_new_game.select();
	}
	Sleep(200);
}

void EndGameMenu::run()
{
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		|| (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)))
		selectNext();

	// if u use more option is like run() og PauseMenu..
}

void EndGameMenu::update(sf::Vector2u size)
{
	m_new_game.setPos(size.x / 2 - 100, size.y / 3);
	m_exit.setPos(size.x / 2 - 100, size.y / 3 + 120);
}


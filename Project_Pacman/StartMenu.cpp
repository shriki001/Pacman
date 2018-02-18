#include "StartMenu.h"
#include <SFML/Graphics.hpp>

//---------------------------------------------------------------------------//
/*
*
*/
StartMenu::StartMenu()
{
	m_frame_texture.loadFromFile("Image\\bg.png");
	m_frame.setTexture(m_frame_texture);

	m_help_texture.loadFromFile("Image\\brief.png");
	m_help.setTexture(m_help_texture);

	pushButton("\tNew Game");
	pushButton("\tlast Game");
	pushButton("\t\tHelp");
	pushButton("  Sound ON");
	pushButton("\tExit Game");

	m_toolBar[0].select();

	m_font.loadFromFile("font.ttf");
	m_startMessage2.setString("Not you? - Press 'N'");
	m_startMessage2.setFont(m_font);
	m_startMessage2.setFillColor(sf::Color::Yellow);
	m_startMessage2.setCharacterSize(20);
	m_startMessage2.setPosition(410, 140);

}

//----------------------------------------------------------------------------//
/*
 *	This
 */
void StartMenu::draw(sf::RenderWindow& app) const
{
	app.draw(m_frame);
	Menu::draw(app);
	drawMsg2(app);
}

//---------------------------------------------------------------------------//
/*
 *
 */
void StartMenu::update(sf::Vector2u size)
{
	m_toolBar[0].setPos(size.x / 2 - 100, size.y / 3);
	m_toolBar[1].setPos(size.x / 2 - 100, size.y / 3 + 60);
	m_toolBar[2].setPos(size.x / 2 - 95, size.y / 3 + 120);
	m_toolBar[3].setPos(size.x / 2 - 90, size.y / 3 + 180);
	m_toolBar[4].setPos(size.x / 2 - 100, size.y / 3 + 240);

}

//---------------------------------------------------------------------------//
/*
 *
 */
ButtonDesc StartMenu::isSelected() const
{
	if (m_selected == m_toolBar.size() - 1)		// last button
		return EXIT_T;

	else if (m_selected == m_toolBar.size() - 2)   // penultimate button
		return TOGGLE_SOUND_T;

	return ButtonDesc(m_selected);
}

//---------------------------------------------------------------------------//
/*
 *
 */
void StartMenu::briefWindow(sf::RenderWindow& window)
{
	sf::Event event;

	while (window.isOpen())
	{
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::KeyPressed)
			{
				switch (event.key.code) {
				    case sf::Keyboard::Escape:
				    case sf::Keyboard::Return:
						return;
				}
			}
		}
		window.draw(m_help);
		window.display();
		window.clear();
	}
}


//---------------------------------------------------------------------------//
/*
 *
 */
void StartMenu::drawMsg2(sf::RenderWindow & window) const
{
	window.draw(m_startMessage2);
}

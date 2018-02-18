
#include "PauseMenu.h"

//---------------------------------------------------------------------------//
/*
 *
 */
PauseMenu::PauseMenu()
	:m_frame(sf::Vector2f(10000,10000))
{
	m_frame.setFillColor(sf::Color(0, 0, 0, 150));
	m_frame.setPosition(0, 60);
	pushButton("\tContinue");
	pushButton("Restart  Level");
	pushButton("Restart  Game");
	pushButton("  Save Game");
	pushButton("  Sound ON");
	pushButton("  Exit  Game");
	m_toolBar[0].select();
}

 ButtonDesc PauseMenu::isSelected() const
 {
	 if (m_selected == m_toolBar.size() - 1)
		 return EXIT_T;
	 else if (m_selected == m_toolBar.size() - 2)
		 return TOGGLE_SOUND_T;
	 return ButtonDesc(m_selected + 10);
 }

//---------------------------------------------------------------------------//
/*
 *
 */
void PauseMenu::draw(sf::RenderWindow & app) const
{
	app.draw(m_frame);
	Menu::draw(app);

} 

//---------------------------------------------------------------------------//
/*
 *
 */
void PauseMenu::update(sf::Vector2u size)
{
	m_toolBar[0].setPos(size.x / 2 - 100, size.y / 3);
	m_toolBar[1].setPos(size.x / 2 - 100, size.y / 3 + 40);
	m_toolBar[2].setPos(size.x / 2 - 100, size.y / 3 + 80);
	m_toolBar[3].setPos(size.x / 2 - 100, size.y / 3 + 120);
	m_toolBar[4].setPos(size.x / 2 - 100, size.y / 3 + 160);
	m_toolBar[5].setPos(size.x / 2 - 100, size.y / 3 + 200);
}
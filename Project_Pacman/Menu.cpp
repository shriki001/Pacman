#include "Menu.h"


//---------------------------------------------------------------------------//
/*
 * Constructor of menu.
 * first button is selected by default
 */
Menu::Menu()
	:m_selected(0)
{
}


//---------------------------------------------------------------------------//
/*
 * This method get a booolean tells if the sound is muted 
 * if so, change the Sound ON button into Sound OFF and vice-versa
 */
void Menu::fixSoundString(bool mute)
{
	if (mute)
		m_toolBar[m_toolBar.size() - 2].setName("  Sound OFF");
	else
		m_toolBar[m_toolBar.size() - 2].setName("  Sound ON");
}

//---------------------------------------------------------------------------//
/*
 *  This method gets a render window. draws the menu on this window.
 */
void Menu::draw(sf::RenderWindow& app) const
{
	for (int i = 0; i < m_toolBar.size(); i++)
		m_toolBar[i].draw(app);
	
}

//---------------------------------------------------------------------------//
/*
 * This method gets selects the next button on the menu.
 * updates the selection colors
 */
void Menu::selectNext()
{
	m_toolBar[m_selected++].unSelect();
	if (m_selected > m_toolBar.size() - 1)
		m_selected = 0;
	m_toolBar[m_selected].select();
}

//---------------------------------------------------------------------------//
/*
 * This method gets selects the prevoius button on the menu.
 * updates the selection colors
 */
void Menu::selectPrev()
{
	m_toolBar[m_selected--].unSelect();
	if ((int)m_selected < 0)
		m_selected = m_toolBar.size() - 1;
	m_toolBar[m_selected].select();
}

//---------------------------------------------------------------------------//
/*
 * The main Method of the menu
 */
void Menu::run(SoundManager& sound)
{
	fixSoundString(!sound.isSoundOn());
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		if (sound.isSoundOn())
			sound.playMenuPass();
		Sleep(200);
		selectNext();
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		if (sound.isSoundOn())
			sound.playMenuPass();
		Sleep(200);
		selectPrev();
	}

	// performed a button
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
	{
		if (sound.isSoundOn())
			sound.playMenuOk();
	}
}

//---------------------------------------------------------------------------//
/*
 *  This method get a name of a new string
 *  push it to the end of the button list
 */
void Menu::pushButton(std::string name)
{
	Button newButton;
	newButton.setName(name);
	m_toolBar.push_back(newButton);
}


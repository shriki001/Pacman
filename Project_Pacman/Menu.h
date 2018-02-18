#pragma once

#include "Button.h"
#include "SoundManager.h"
#include "windows.h"
class Menu
{
public:
	Menu();
	
	virtual void update(sf::Vector2u size) = 0;  // update Button location     
	virtual ButtonDesc isSelected() const = 0;  // return Button type
	void draw(sf::RenderWindow& app) const;     // draw Button
	void selectNext();                         // select next Button
	void selectPrev();                      // select previews Button
	virtual void fixSoundString(bool mute); // change Sound ON/OFF Button name
	void run(SoundManager& sound);          // play menu arrow down & up
	void pushButton(std::string name);      // set up new Button to menus

protected:
	std::vector<Button> m_toolBar;       // Button Data Structure
	size_t m_selected;
};


#pragma once
#include <string>
#include <SFML\Graphics.hpp>

// struct that contain text parameters
struct GameText
{
	GameText(const std::string& textName,
	    	const char* fontFileName,
	    	const int fontSize)
	{
		m_text.setString(textName);
		m_font.loadFromFile(fontFileName);
		m_text.setFont(m_font);
		m_text.setCharacterSize(fontSize);
	}

	std::string m_fontFile;
	sf::Font m_font;
	sf::Text m_text;
};

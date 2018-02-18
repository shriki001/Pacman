#include "UtilWindows.h"

//---------------------------------------------------------------------------//
/*
 * util function to open a window of announcment
 */
void openMsgWin(std::string WindowTitle, std::string WindowMsgTxt, sf::Color color)
{
	sf::RenderWindow ask(sf::VideoMode(500, 200), WindowTitle, sf::Style::None);
	sf::Event event;
	makeWindowOnTop(ask);
	GameText msg(WindowMsgTxt, "font.ttf", 40);
	msg.m_text.setPosition(10.f, 30.f);
	msg.m_text.setFillColor(color);

	while (ask.isOpen())
	{
		while (ask.pollEvent(event))
		{
			if (event.type == sf::Event::KeyPressed)
			{
				switch (event.key.code)
				{
				case sf::Keyboard::Escape:
				case sf::Keyboard::Return:
					ask.close();
					Sleep(500);
				}
			}
		}
		ask.draw(msg.m_text);
		ask.display();
		ask.clear();
	}
}
//---------------------------------------------------------------------------//
/*
 * util function to open a prompt window of yes-no question
 */
// true = YES, false = NO
bool openAskWin(std::string WindowTitle)
{
	sf::RenderWindow ask(sf::VideoMode(400, 200), WindowTitle, sf::Style::Titlebar);
	makeWindowOnTop(ask);
	sf::Event event;
	sf::Font font;
	font.loadFromFile("font.ttf");
	sf::Text ansY("Yes", font, 40);		// "Yes" answer text
	sf::Text ansN("No", font, 40);      // "No" answer text
	ansY.setPosition(120, 70.f);
	ansN.setPosition(230, 70.f);
	ansY.setFillColor(sf::Color::Red);
	ansN.setFillColor(sf::Color::White);

	while (ask.isOpen()) {
		while (ask.waitEvent(event))
		{
			switch (event.type) {
			case sf::Event::KeyPressed:
				switch (event.key.code)
				{
				case sf::Keyboard::Left:
					ansY.setFillColor(sf::Color::Red);
					ansN.setFillColor(sf::Color::White);
					break;
				case sf::Keyboard::Right:
					ansN.setFillColor(sf::Color::Red);
					ansY.setFillColor(sf::Color::White);
					break;
				case sf::Keyboard::Return:
					if (ansY.getFillColor() == sf::Color::Red)
					{
						ask.close();
						return true;
					}
					else if (ansN.getFillColor() == sf::Color::Red)
					{
						ask.close();
						Sleep(500);
						return false;
					}
					break;
				}
			}
			ask.draw(ansY);
			ask.draw(ansN);
			ask.display();
			ask.clear();
		}
	}
	return false;
}

//---------------------------------------------------------------------------//
/*
 * util function to set window on top of desktop environment
 */
void makeWindowOnTop(sf::RenderWindow& window)
{
	HWND hwnd = window.getSystemHandle();
	SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
}
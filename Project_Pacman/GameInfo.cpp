#include "GameInfo.h"
#include "Settings.h"


//---------------------------------------------------------------------------//
/*
 * Constructor of Game information in the game
 */
GameInfo::GameInfo(int currlvl, int score, int life)
	:m_currlvl(currlvl), m_score(score), m_life(life)
{
	m_font.loadFromFile("font.ttf");
	m_livesTxt.setFont(m_font);
	m_scoreTxt.setFont(m_font);
	m_levelTxt.setFont(m_font);
	m_cookieTimer.setFont(m_font);
	m_elapsedTime.setFont(m_font);
	m_nameTxt.setFont(m_font);

	setUpTXT(m_scoreTxt, sf::Color::White);
	setUpTXT(m_levelTxt, sf::Color::Yellow);
	setUpTXT(m_livesTxt, sf::Color(100, 155, 155));
	setUpTXT(m_cookieTimer, sf::Color::Cyan);
	setUpTXT(m_elapsedTime, sf::Color::Cyan);

	m_nameTxt.setFillColor(sf::Color::White);
	m_nameTxt.setOutlineThickness(3);
	m_nameTxt.setOutlineColor(sf::Color::Black);

	updateScore(0);
	updateLives(0);
	updateLevelNum(0);
}

void GameInfo::setUpTXT(sf::Text& txt, sf::Color color)
{
	txt.setFillColor(color);
	txt.setOutlineThickness(3);
	txt.setOutlineColor(sf::Color::Black);
}

//---------------------------------------------------------------------------//
/*
 * This method set the a new score of the game
 */
void GameInfo::resetScore(int x)
{
	m_score = x;
}

//---------------------------------------------------------------------------//
/*
 * This method set the a new number lives of the game
 */
void GameInfo::resetlife(int x)
{
	m_life = x;
}

//---------------------------------------------------------------------------//
/*
 * This method set the a new level number of the game
 */
void GameInfo::resetlevel(int x)
{
	m_currlvl = x;
}

//---------------------------------------------------------------------------//
/*
 * This method update the current score in the game
 */
void GameInfo::updateScore(int x)
{
	m_score += x;
}

//---------------------------------------------------------------------------//
/*
 * This method update the current lives in the game
 */
void GameInfo::updateLives(int x)
{
	m_life += x;
}

//---------------------------------------------------------------------------//
/*
 * This method update the current level number in the game
 */
void GameInfo::updateLevelNum(int x)
{
	m_currlvl += x;
}

//---------------------------------------------------------------------------//
/*
 * This method returns the current score in the game
 */
void GameInfo::resetTimerText(int sec)
{
	if (sec == -1)			// time is out
		m_cookieTimer.setString("\t\t\t\t\t");
	else
		m_cookieTimer.setString("Time left: " + std::to_string(sec));
}

//---------------------------------------------------------------------------//
/*
 * This method gets a the number of seconds that elpased from start of the game
 * update the timer text
 */
void GameInfo::resetGameTimeText(int secs)
{
	int minute = secs / 60;				// keep divid of time to dd::mm
	
	// coverts numbers into string
	std::string minutesElapsed = std::to_string(minute),
		        secondsElapsed = std::to_string(secs % 60);
	// fixing the mintues:second to be correct
	if (minute < 10)
		minutesElapsed = "0" + minutesElapsed;
	if (secs % 60 < 10)
		secondsElapsed = "0" + secondsElapsed;
	m_elapsedTime.setString("Time Elapsed: " + minutesElapsed + ":"
		+ secondsElapsed);
}

//---------------------------------------------------------------------------//
/*
 *  This method gets a render window.
 *  draws all the info related to the game on this window
 */
void GameInfo::drawPlayerName(sf::RenderWindow& window)
{
	m_nameTxt.setPosition(425.f - (m_name.size()*6.f), 100.f);
	window.draw(m_nameTxt);
}

//---------------------------------------------------------------------------//
/*
 *  This method gets a render window.
 *  draws all the info related to the game on this window
 */
void GameInfo::showInfo(sf::RenderWindow & window) const
{
	sf::RectangleShape bg(sf::Vector2f(1000, 60));
	bg.setFillColor(sf::Color::Black);
	// draw background and the info texts
	window.draw(bg);
	window.draw(m_scoreTxt);
	window.draw(m_livesTxt);
	window.draw(m_levelTxt);
	window.draw(m_elapsedTime);
	// draws timer only if time is not done
	if (m_cookieTimer.getString() != "Time left: 0")
		window.draw(m_cookieTimer);
}


//---------------------------------------------------------------------------//
/*
 *
 */
void GameInfo::updatePositions(int screenLength, int screenWidth)
{
	m_levelTxt.setCharacterSize(screenLength / 18);
	m_scoreTxt.setCharacterSize(screenLength / 18);
	m_livesTxt.setCharacterSize(screenLength / 18);
	m_cookieTimer.setCharacterSize(screenLength / 18);
	m_elapsedTime.setCharacterSize(screenLength / 18);

	m_scoreTxt.setPosition(0, 10);
	m_livesTxt.setPosition(screenLength / 3.0f*1.1f, 10);
	m_levelTxt.setPosition(screenLength / 3.0f*2.2f, 10);
	m_cookieTimer.setPosition(5.f, screenWidth - 60.f);
	m_elapsedTime.setPosition(screenLength / 3.0f*1.2f, screenWidth - 60.f);
}

//---------------------------------------------------------------------------//
/*
 * 
 */
void GameInfo::openWelcome()
{
	sf::RenderWindow window2(sf::VideoMode(400, 200), "Welcome Player", sf::Style::Titlebar);
	sf::Event event;
	sf::Font font;
	font.loadFromFile("font.ttf");
	sf::Text text("", font, 40);
	text.setFillColor(sf::Color::White);
	text.setPosition(sf::Vector2f(85, 90));
	std::string msgWelcome = "Enter your name :\n\n";

	sf::Text startMessage(msgWelcome, font, 40);
	startMessage.setFillColor(sf::Color::White);
	makeWindowOnTop(window2);

	while (window2.isOpen())
	{
		while (window2.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::KeyPressed:
				int key = (event.key.code);
				if (key == sf::Keyboard::Return && m_name.size() != 0)
				{
					window2.close();
					return;
				}
				else if (m_name.size() <= MAX_NAME_LEN)
				{
					if (key >= sf::Keyboard::A && key <= sf::Keyboard::Z)
					{
						if (m_name.size() == 0)
							m_name += char(key + 'A');
						else
							m_name += char(key + 'a');
					}
					else if (key >= sf::Keyboard::Numpad0 && key <= sf::Keyboard::Numpad9)
						m_name += char(key - 27);
					else if (key >= sf::Keyboard::Num0 && key <= sf::Keyboard::Num9)
						m_name += char(key + 22);
					else if (key == sf::Keyboard::Space)
						m_name += ' ';
				}
				if (key == sf::Keyboard::BackSpace)		// for delete a char
				{
					std::string temp = m_name.substr(0, m_name.size() - 1);
					m_name = temp;
				}
			}
		}
		text.setString(m_name);
		window2.draw(startMessage);

		window2.draw(text);
		window2.display();
		window2.clear();
		m_nameTxt.setString("Welcome " + m_name + " !");
	}
}

//---------------------------------------------------------------------------//
/*
 * This method returns the current score in the game
 */
size_t GameInfo::score() const
{
	return m_score;
}

//---------------------------------------------------------------------------//
/*
 * This method returns the current lives of player in the game
 */
size_t GameInfo::life() const
{
	return m_life;
}

//---------------------------------------------------------------------------//
/*
 * This method returns the current level of the game
 */
size_t GameInfo::currlvl() const
{
	return m_currlvl;
}

//---------------------------------------------------------------------------//
/*
 * This method returns the player's (nick-)name
 */
std::string GameInfo::getName() const
{
	return m_name;
}

//---------------------------------------------------------------------------//
/*
 * This method returns the player's (nick-)name
 */
void GameInfo::updateTexts()
{
	m_levelTxt.setString("Level: " + std::to_string(m_currlvl));
	m_livesTxt.setString("Life: " + std::to_string(m_life));
	m_scoreTxt.setString("Score: " + std::to_string(m_score));
}
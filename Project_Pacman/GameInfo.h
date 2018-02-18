#pragma once
#include "UtilWindows.h"

class GameInfo
{
public:
	GameInfo(int, int ,int);
	// reset player Score text
	void resetScore(int x);
	//reset player level text
	void resetlevel(int x);
	//reset player life text
	void resetlife(int x);
	//update player score text
	void updateScore(int); 
	//update player life text
	void updateLives(int); 
	//update player level text
	void updateLevelNum(int);
	//restart cookie timer
	void resetTimerText(int);
	// restart Game timer
	void resetGameTimeText(int secs);
	// show all info text						
	void showInfo(sf::RenderWindow & window) const;
	// update all text position as window size
	void updatePositions(int screenLength, int );
	// return player score
	size_t score() const;
	// return player life
	size_t life() const; 
	// return current game level
	size_t currlvl() const;
	// open welcome Player window
	void openWelcome(); 

	// set all texture's  
	void setUpTXT(sf::Text&,sf::Color);

	// get Player name
	std::string getName() const; 

	void drawPlayerName(sf::RenderWindow & window);
	void updateTexts();
private:
	size_t m_life;				// keeps player's life
	int m_score;				// keep player's score 
	size_t m_currlvl;			// keep current level number
	std::string m_name;			// keeps name of Player
	
	sf::Text m_livesTxt;
	sf::Text m_scoreTxt;
	sf::Text m_levelTxt;
	sf::Text m_nameTxt;
	sf::Font m_font;

	sf::Text m_cookieTimer;		// cookie timer member
	sf::Text m_elapsedTime;		// game timer member
};






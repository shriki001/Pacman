#pragma once

#include "Board.h"
#include "Collusion.h"
#include "Cookie.h"
#include "Wall.h"
#include "GameInfo.h" 
#include "PauseMenu.h" 
#include "StartMenu.h" 

class GameManager
{
public:
	GameManager();
	~GameManager();
	void run();      // run all game


private:
	/***	class members	  ***/
	int m_CookiesAte;
	Board m_gameMap;
	Collusion m_Collider;
	SoundManager m_sound;
	sf::Clock m_gameClock;
	sf::Clock m_timer;
	GameInfo m_info;
	CookieType m_lastCookie;
	PauseMenu m_pauseScreen;
	StartMenu m_startScreen;
	sf::RenderWindow m_window;				// Game window
	PlayerP* m_player;						// Player Pacman
	std::vector <PlayerD*> m_players_demon; // ghost vector
	std::vector<sf::Vector2f> m_locations; // character location vector
	bool m_firstUse;

	/***	  private methods	  ***/
	void drawGame();                    // draw characters, map and info
	void resetWindow();                 // in charge of window re-size
	void isPlayerDied();			    // in charge of Player death 
	void showLevelPreview();			// shows the level preview


	void updateLocations();			// update character location
	void resetlocations();			// reset character location

	bool loadLevel(size_t);			   // load new level
	bool loadStartScreen();			   // in charge of start screen
	bool loadPauseScreen(int);         // in charge of pause screen
	void endOfGame();				   // ending the game
	void Update();				       // in charge of character movement
	void resetlevel(size_t
	);           // reset current level
	void PlayerPlay();				  // in charge of Pacman move
	void DemonPlay(size_t id);        // in charge of Ghost move
							   
    // new direction checker for character (generic) 
	bool ControlPlayer(PlayerState dir, Player *); 
	// new direction checker from wall in sides (generic)
	bool canPlayerMove(PlayerState dir, Player * pld);
	// checks if player moved out of map bounds
	bool isPlayerReachBounds(PlayerState dir, Player * pld);
	// new direction checker for character move in axis (generic)
	bool checkAxis(PlayerState dir, Player * pld);
	// new direction checker for grid bounds (generic)
	bool checkBounds(PlayerState dir, Player * pld);
	void reloadCurrLevel(int oldScore);		// reload current level
	void resetGame();        			// restart the Game
	void ateCookie(CookieType);	       // in charge of cookie eating
	void cookieAffect();		       // in charge of cookie affect on Pacman
	void startNewGame();	           // starting a new game 


};


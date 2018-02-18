#include "GameManager.h"
#include <windows.h>

static const std::string GAME_TItlE = "Pacman Game ";

//---------------------------------------------------------------------------//
/*
 * Constructor of GameManger
 * defines the initial setting of the game
 */
GameManager::GameManager()
	:m_info(1, 0, LIFE),
	m_CookiesAte(0),
	m_firstUse(true)
{ }

//---------------------------------------------------------------------------//
/*
 *  Destructor of GameManger class
 *  cleans all the pointers used
 */
GameManager::~GameManager()
{
	for (int i = 0; i < m_players_demon.size(); i++)
		if (m_players_demon[i] != nullptr)
			delete m_players_demon[i];

	if (m_player != nullptr)
		delete m_player;
}

//---------------------------------------------------------------------------//
/*
 * This method gets void
 * Update the locations of all the characters on the game, for
 * remembering positions when player restart a level
 */
void GameManager::updateLocations()
{
	sf::Vector2f temp;
	temp = m_player->getPosition();
	m_locations.push_back(temp);

	for (int i = 0; i < m_players_demon.size(); i++)
	{
		temp = (m_players_demon[i])->getPosition();
		m_locations.push_back(temp);
	}
}

//---------------------------------------------------------------------------//
/*
 * This method gets void
 * Resets back the locations of all the characters on the game, for
 * initial positions when player started a level
 */
void GameManager::resetlocations()
{
	//  reset player's location
	m_player->setPosition(m_locations[0]);

	// reset demons' locations
	for (int i = 0; i < m_players_demon.size(); i++)
		(m_players_demon[i])->setPosition(m_locations[i + 1]);
}

//---------------------------------------------------------------------------//
/*
 *	This method gets a number of the level needed to be load
 *	if the level's file exist, load from the file and returns true.
 *	otherwise, we finished all levels.
 */
bool GameManager::loadLevel(size_t levelNum)
{
	// sets the path of the level we want to load in game.
	std::string levelfile = "Levels\\lvl" + std::to_string(levelNum) + ".txt";

	// try to load a level from file, if failed we loaded all files
	// means that our player have won
	if (!m_gameMap.loadFromFile(levelfile, m_player, m_players_demon))
	{
		endOfGame();
		return false;
	}

	m_locations.clear();		// reset vector of locations
	updateLocations();          // update locations of characters
	resetWindow();
	return true;
}

//---------------------------------------------------------------------------//
/*
 * This method loads the first Opening Screen when Game is running
 */
bool GameManager::loadStartScreen()
{
	sf::Event evnt;
	bool out = false;
	m_startScreen.update(sf::Vector2u(1024, 800));
	m_window.create(sf::VideoMode(1024, 800), "Pacman Game", sf::Style::Titlebar);
	m_startScreen.draw(m_window);
	m_window.display();
	
	if (m_firstUse)
	{
		m_info.openWelcome();
		m_firstUse = false;
	}
	
	m_sound.playIntro();
	while (m_window.isOpen())
	{
		while (m_window.pollEvent(evnt))
		{
			m_startScreen.run(m_sound);

			// press 'n' to change your name
			if (evnt.type == sf::Event::KeyPressed &&
				evnt.key.code == sf::Keyboard::N)
				m_info.openWelcome();

			while (evnt.type == sf::Event::KeyPressed &&
				evnt.key.code == sf::Keyboard::Return)
			{
				switch (m_startScreen.isSelected())
				{
				case NEW_GAME_T:
					return true;

				case LOAD_GAME_T:
					openMsgWin("", "Cant Open in Trial Version\n"
						"Please Buy the Full Version", sf::Color::Red);
					out = true;
					break;
				
				case HELP_T:
					m_startScreen.briefWindow(m_window);
					out = true;
					break;

				case TOGGLE_SOUND_T:
					m_sound.Mute();
					out = true;
					break;
				case EXIT_T:
					if (openAskWin("Are you sure?"))
					{
						m_window.close();
						return false;
					}
					else
						out = true;
					break;
				}
				if (out)
					break;
			}

			m_startScreen.draw(m_window);
			m_info.drawPlayerName(m_window);
			m_window.display();
		}
	}
	return true;
}

//---------------------------------------------------------------------------//
/*
 * This method loading the pause screen
 * gets the current score if player choose to re-start playing the level
 */
bool GameManager::loadPauseScreen(int last_score)
{
	Sleep(200);
	sf::Event evnt;
	bool out = false;
	while (m_window.isOpen())
	{
		while (m_window.pollEvent(evnt))
		{
			m_pauseScreen.run(m_sound);
			while (evnt.type == sf::Event::KeyPressed &&
				evnt.key.code == sf::Keyboard::Return)
			{
				switch (m_pauseScreen.isSelected())
				{
				case CONTINUE_T:
					return true;

				case RESTART_LEVEL_T:
					reloadCurrLevel(last_score);
					return true;
					break;

				case RESTART_GAME_T:
					if (openAskWin("Are you sure?"))
					{
						m_window.close();
						resetGame();
						startNewGame();
						return false;  
					}
					else
						out = true;
					break;

				case TOGGLE_SOUND_T:
					m_sound.Mute();
					out = true;
					break;

				case SAVE_GAME_T:
					openMsgWin("", "Cant Open in Trial Version\n"
						"Please Buy the Full Version", sf::Color::Red);
					out = true;
					break;

				case EXIT_T:
					if (openAskWin("Are you sure?"))
					{
						m_window.close();
						return false;
					}
					else
						out = true;
					break;
				}
				if (out)
					break;
			}
		}
		m_window.clear();
		drawGame();
		m_pauseScreen.draw(m_window);
		m_window.display();
	}
	return true;
}

//---------------------------------------------------------------------------//
/*
 *
 */
void GameManager::run()
{
	sf::Event event;
	int last_score = 0;
	Sleep(200);
	startNewGame();

	while (m_window.isOpen())
	{
		while (m_window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				return;
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::S)
					m_gameMap.resetCookies();
				if (event.key.code == sf::Keyboard::L)
				{
					m_player->addLife();
					m_info.resetlife((int)m_player->getlives());
				}
			}
		}
		// user choose to pause the game
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			m_sound.playGamePause();
			if (!loadPauseScreen(last_score) && m_pauseScreen.isSelected()== EXIT_T)
				return;
		}
		// as long as player is alive
		if (m_player->isAlive())
		{
			if (m_gameMap.cookiesLeft() == 0)
			{
				m_info.updateLevelNum(1);
				size_t m_currLevel = m_info.currlvl();
				m_info.updateScore(+50 * (int)(m_players_demon.size() + 1));
				m_player->setStayDirect(STAY_T);
				last_score = (int)m_info.score();
				m_player->setlife((int)m_info.life());
				if (!loadLevel(m_currLevel))
				{
					startNewGame();
					continue;
				}
			}
			m_window.clear();
			Update();
			cookieAffect();
			drawGame();
			m_window.display();  // show the game window
		}

		else			//  our player is DEAD 
		{
			m_sound.playGameOver();
			openMsgWin("Game OVER!!", "\t\t\t\tU have died\n \t\t   the game is over\n   \t\t\t Press Enter", sf::Color::Cyan);
			resetGame();
			startNewGame();
		}
	}
}

//---------------------------------------------------------------------------//
/*
 * This method performs end of game when player won
 */
void GameManager::endOfGame()
{
	int start = (int)m_gameClock.getElapsedTime().asSeconds();
	int end;
	m_sound.playWin();
	sf::RectangleShape rec;
	sf::Texture t;
	t.loadFromFile("Image\\winGame.png");
	rec.setTexture(&t);
	rec.setSize((sf::Vector2f)m_window.getSize());

	std::string WindowMsgTxt = "\t\t\t\tCongratulations " + m_info.getName() + "! \n"
		"\t\t\t\t\t\t U WIN!!\n"
		"\t\t You have finished the game";
	GameText msg(WindowMsgTxt, "font.ttf", 35);
	msg.m_text.setPosition(10.f, 30.f);
	msg.m_text.setFillColor(sf::Color::Cyan);
	m_window.draw(msg.m_text);
	m_window.display();
	GameText msg2 = msg;
	msg2.m_text.setPosition(10.f, 230.f);
	msg2.m_text.setFillColor(sf::Color::Black);
	msg2.m_text.setString("\tFinal Score: " + std::to_string(m_info.score()));

	do {
		end = (int)m_gameClock.getElapsedTime().asSeconds();
		m_window.clear();
		m_window.draw(rec);
		m_window.draw(msg.m_text);
		m_window.draw(msg2.m_text);
		
		m_window.display();
		if ((int)m_gameClock.getElapsedTime().asSeconds() % 3 == 0)
			msg.m_text.setFillColor(sf::Color::Blue);
		else if ((int)m_gameClock.getElapsedTime().asSeconds() % 3 == 1)
			msg.m_text.setFillColor(sf::Color::Green);
		else
			msg.m_text.setFillColor(sf::Color::Magenta);
	} while (end - start < 10);

	resetGame();
}

//---------------------------------------------------------------------------//
/*
 *  This method performs an update to the game window
 */
void GameManager::Update()
{
	// play Characters
	PlayerPlay();
	if (m_players_demon.size() > 0)
		for (size_t i = 0; i < m_players_demon.size(); i++)
			DemonPlay(i);
	
	isPlayerDied();   // check if player have died

	//  draw time elapsed from beginning of the game
	m_info.resetGameTimeText((int)m_gameClock.getElapsedTime().asSeconds());

	// update texts on screen
	m_info.updateTexts();
}

//---------------------------------------------------------------------------//
/*
 * manage Pacman moves
 */
void GameManager::PlayerPlay()
{
	Player * tmp = dynamic_cast<Player*> (m_player);
	PlayerState newD = tmp->setNewDirect(tmp->getNew());

	if (ControlPlayer(newD, tmp) && canPlayerMove(newD, tmp))
		tmp->playMove(newD);

	else if (ControlPlayer(tmp->getDirection(), tmp))
		tmp->playMove(tmp->getDirection());
}

//---------------------------------------------------------------------------//
/*
 * manage Demon moves
 */
void GameManager::DemonPlay(size_t id)
{
	Player* tmp = dynamic_cast<Player*>(m_players_demon[id]);
	PlayerState newD = tmp->setNewDirect(tmp->getNew());

	if (dynamic_cast<SmartDemon*>(m_players_demon[id]->getObject()))
	{
		if ((int)m_gameClock.getElapsedTime().asSeconds() % 3 != 0)
			newD = m_players_demon[id]->smartMove2(m_player, m_gameMap.getGridSize());
		else
			m_players_demon[id]->smartMove(m_player->getDirection());
	}
	if (ControlPlayer(newD, tmp) && canPlayerMove(newD, tmp))
		tmp->playMove(newD);

	else if (ControlPlayer(tmp->getDirection(), tmp))
		tmp->playMove(tmp->getDirection());
}

//---------------------------------------------------------------------------//
/*
 *  This method checks if the player died because touched on
 */
void GameManager::isPlayerDied()
{
	for (int i = 0; i < m_players_demon.size(); i++)
	{
		if (m_Collider.isPacmanCollidedGhost
		(*(m_player->getObject()), dynamic_cast<Demon*>(m_players_demon[i]->getObject())))
		{
			m_sound.playLoseLife();
			Sleep(1000);
			m_player->kill();
			m_info.updateLives(-1);
			m_player->setlife(m_info.life());
			resetlevel(m_info.currlvl());
			break;
		}
	}
}
//---------------------------------------------------------------------------//
/*
 * This method reset the game for playing the current level again
 */
void GameManager::reloadCurrLevel(int oldScore)
{
	m_gameMap.resetCookies();
	loadLevel(m_info.currlvl());
	m_info.resetScore(oldScore);
	m_player->setStayDirect(STAY_T);		// reset player state
}

//---------------------------------------------------------------------------//
/*
 * This method reset the game to initial mode
 */
void GameManager::resetGame()
{
	Sleep(1000);
	m_info.resetScore(0);
	m_gameMap.resetCookies();
	m_info.resetlife(LIFE);
	m_info.resetlevel(1);
	m_window.close();
}

//---------------------------------------------------------------------------//
/*
 * This function gets a type of the cookie that player ate
 * Updates his speed if its a non-regular cookie
 * Add one to his lives if 200 eaten ,also update the score
 */
void GameManager::ateCookie(CookieType type_ate)
{
	float currPlayerSpeed = m_player->getSpeed();
	m_sound.playAteCookie();

	switch (type_ate)
	{
	case HEALTHY_T:
		if (currPlayerSpeed*1.2f < MAX_SPEED)
			m_player->setSpeed(currPlayerSpeed*1.2f);
		else
			m_player->setSpeed(MAX_SPEED);
		break;

	case POSION_T:
		if (currPlayerSpeed*0.8f > MIN_SPEED)
			m_player->setSpeed(currPlayerSpeed*0.8f);
		else
			m_player->setSpeed(MIN_SPEED);
		break;
	}

	if (type_ate != NORMAL_T){
		m_lastCookie = type_ate;
		m_timer.restart();
	}

	m_CookiesAte++;
	if (m_CookiesAte == COOKIE_LIMIT)  		// eaten enough to get 1-UP
	{	
		m_CookiesAte = 0;
		m_info.updateLives(1);
		m_player->setlife((int)m_info.life());
	}
	m_info.updateScore(+2 * (int)(m_players_demon.size() + 1));
	m_gameMap.addCookies(-1);
}

//---------------------------------------------------------------------------//
/*
 *
 */
void GameManager::resetlevel(size_t level_num)
{
	resetlocations();
	int currCookie = m_gameMap.cookiesLeft();
	m_gameMap.resetCookies();
	m_gameMap.addCookies(currCookie);
	showLevelPreview();
}

//---------------------------------------------------------------------------//
/*
 * This method draws all the game's components.
 * Draws the game's map, characters and info
 */
void GameManager::drawGame()
{
	// Draw Map
	m_gameMap.display(m_window);

	// Draw Characters
	m_player->draw(m_window);
	for (size_t i = 0; i < m_players_demon.size(); i++)
		m_players_demon[i]->draw(m_window);

	// Draw Game Info
	m_info.showInfo(m_window);
}

//---------------------------------------------------------------------------//
/*
 *	This method resets the window according to the size of map of a certain
 *	level.
 */
void GameManager::resetWindow()
{
	sf::Vector2u VideoSize;

	VideoSize.y = m_gameMap.getGridSize().x * SIZE1 + 4 * SIZE1;
	VideoSize.x = m_gameMap.getGridSize().y * SIZE1;
	m_window.create(sf::VideoMode(VideoSize.x, VideoSize.y),
		GAME_TItlE, sf::Style::Titlebar);
	makeWindowOnTop(m_window);

	m_window.setFramerateLimit(100);
	showLevelPreview();

	m_info.updatePositions(VideoSize.x, VideoSize.y);
	m_pauseScreen.update(VideoSize);
}

//---------------------------------------------------------------------------//
/*
 * This Method print the number of level and player's current lives before the
 * level starts
 */

void GameManager::showLevelPreview()
{
	sf::Sprite PacmanImg;
	sf::Texture PacmanImgTexture;
	PacmanImgTexture.loadFromFile("Image\\pacman.png");
	PacmanImg.setTexture(PacmanImgTexture);
	if (m_player->isAlive())
	{
		m_window.clear();
		sf::Font fnt;
		fnt.loadFromFile("font.ttf");
		sf::Text t1("Level " + std::to_string(m_info.currlvl())
			+ "\n    x " + std::to_string(m_info.life()), fnt, 36);

		sf::Vector2u sizeW = m_window.getSize();

		t1.setPosition(sizeW.x / 2.f - 79.f, sizeW.y / 3.f + 40.f);
		PacmanImg.setPosition(sizeW.x / 2.f - 86.f, sizeW.y / 3.f + 90.f);
		t1.setFillColor(sf::Color::White);
		t1.setOutlineThickness(3);
		t1.setOutlineColor(sf::Color::Black);

		m_window.draw(t1);
		m_window.draw(PacmanImg);

		m_window.display();
		Sleep(2000);
	}
}


//---------------------------------------------------------------------------//
/*
 * This method Updates the affection of the cookie on the player.
 * Checks if the affection time run out. if so, reset player's speed to normal.
 */
void GameManager::cookieAffect()
{
	int timeLeft = 0;
	switch (m_lastCookie)		//reset the affection time
	{
	case HEALTHY_T:
		timeLeft = HEALTH_TIME - (int)m_timer.getElapsedTime().asSeconds();
		break;
	case POSION_T:
		timeLeft = POSION_TIME - (int)m_timer.getElapsedTime().asSeconds();
		break;
	}

	if (timeLeft >= 0)
		m_info.resetTimerText(timeLeft);
	else
		m_info.resetTimerText(-1);

	switch (m_lastCookie)    // reset the Pacman's speed when cookie affect time-out
	{
	case HEALTHY_T:
		if ((int)m_timer.getElapsedTime().asSeconds() == HEALTH_TIME)
			m_player->setSpeed(1);
		break;

	case POSION_T:
		if ((int)m_timer.getElapsedTime().asSeconds() == POSION_TIME)
			m_player->setSpeed(1);
		break;
	}
}

//---------------------------------------------------------------------------//
/*
 * This method prepare the game and loads the start screen of the game
 */
void GameManager::startNewGame()
{
	if (!loadStartScreen())
		return;
	m_gameClock.restart();			// reset game clock
	m_info.resetGameTimeText(0);
	loadLevel(1);					// loading the first level
}

/////////////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------------//
/*
 *	This method get a direction of a player, and a pointer to his object
 *	Returns true if he can move to that direction, otherwise returns false
 */
bool GameManager::ControlPlayer(PlayerState dir, Player * pld)
{
	sf::Vector2i gridPos = m_gameMap.fixedPos(pld->getPosition());
	StaticObject * currOBJ = m_gameMap.getGridPos(gridPos.x, gridPos.y);

	if (!checkAxis(dir, pld) || !checkBounds(dir, pld))
		return false;

	if (dynamic_cast<PlayerP*>(pld))
	{
		if (m_Collider.isPacmanCollidedCookie(*(m_player->getObject()),
			dynamic_cast<StaticObject*>(currOBJ)))
		{
			CookieType type_ate = (dynamic_cast<Cookie*>(currOBJ))->getCookieType();
			m_gameMap.clear(gridPos.y, gridPos.x);
			ateCookie(type_ate);
		}
	}
	return true;
}
//---------------------------------------------------------------------------//
/*
 * This method get a direction of a player, and a pointer to his object
 * Returns true if he placed in the grid axises.
 */
bool GameManager::checkAxis(PlayerState dir, Player *pld)
{
	sf::Vector2i gridPos = m_gameMap.fixedPos(pld->getPosition());
	bool canMove = true;

	switch (dir)
	{
	case LEFT_T:
	case RIGHT_T:
		if (std::abs(pld->getCenter().y -
			(((gridPos.y) * SIZE1) + (SIZE1 / 2)) + 1) > 1.f)
			canMove = false;
		break;
	case UP_T:
	case DOWN_T:
		if (std::abs(pld->getCenter().x -
			((gridPos.x * SIZE1) + (SIZE1 / 2)) + 1) > 1.f)
			canMove = false;
		break;
	}
	return canMove;
}

//---------------------------------------------------------------------------//
/*
 * This method get a direction of a player, and a pointer to his object
 * Returns false if he touched the map limit, means he cant move.
 */
bool GameManager::checkBounds(PlayerState dir, Player * pld)
{
	sf::Vector2f currPos = pld->getPosition();
	sf::Vector2i mapSize = m_gameMap.getGridSize();
	sf::Vector2i gridPos = m_gameMap.fixedPos(currPos);
	StaticObject * obj = nullptr;
	StaticObject * obj2 = nullptr;
	bool canMove = true;
	switch (dir)
	{
	case LEFT_T:
		if (currPos.x < 0)
		{
			obj2 = m_gameMap.getGridPos(mapSize.y - 1, gridPos.y);
			if (dynamic_cast<Wall*>(obj2))
			{
				canMove = false;
				pld->getObject()->setState(STAYLEFT_T);
			}
			else currPos.x = (float)(mapSize.y - 1) *SIZE1;
		}
		if (isPlayerReachBounds(dir, pld))
			obj = m_gameMap.getGridPos(gridPos.x - 1, gridPos.y);
		if (m_Collider.CheckCollusion(dynamic_cast<StaticObject*>
			(obj), pld->getObject())) 
		{
			canMove = false;
			currPos.x += pld->getSpeed();
			pld->getObject()->setState(STAYLEFT_T);
		}
		break;
	case RIGHT_T:
		if (currPos.x >= (mapSize.y - 1) *SIZE1)
		{
			obj2 = m_gameMap.getGridPos(0, gridPos.y);
			if (dynamic_cast<Wall*>(obj2))
			{
				canMove = false;
				pld->getObject()->setState(STAY_T);
			}
			else currPos.x = 0;
		}
		if (isPlayerReachBounds(dir, pld))
			obj = m_gameMap.getGridPos(gridPos.x + 1, gridPos.y);
		if (m_Collider.CheckCollusion(dynamic_cast<StaticObject*>(obj),
			pld->getObject())) 
		{
			canMove = false;
			currPos.x -= pld->getSpeed();
			pld->getObject()->setState(STAY_T);
		}
		break;
	case UP_T:
		if (currPos.y <= 2*SIZE1) 
		{
			obj2 = m_gameMap.getGridPos(gridPos.x, mapSize.x - 1);
			if (dynamic_cast<Wall*>(obj2))
			{
				canMove = false;
				pld->getObject()->setState(STAYUP_T);
			}
			else currPos.y = float((mapSize.x - 1) *SIZE1 + 2 * SIZE1);
		}
		if (isPlayerReachBounds(dir, pld))
			obj = m_gameMap.getGridPos(gridPos.x, gridPos.y - 1);
		if (m_Collider.CheckCollusion(dynamic_cast<StaticObject*>(obj),
			pld->getObject())) 
		{
			canMove = false;
			currPos.y += pld->getSpeed();
			pld->getObject()->setState(STAYUP_T);
		}
		break;
	case DOWN_T:
		if (currPos.y >= (mapSize.x + 1) *SIZE1 - 1) 
		{
			obj2 = m_gameMap.getGridPos(gridPos.x, 0);
			if (dynamic_cast<Wall*>(obj2))
			{
				canMove = false;
				pld->getObject()->setState(STAYDOWN_T);
			}
			else currPos.y = 2*SIZE1;
		}
		if (isPlayerReachBounds(dir, pld))
			obj = m_gameMap.getGridPos(gridPos.x, gridPos.y + 1);
		if (m_Collider.CheckCollusion(dynamic_cast<StaticObject*>(obj),
			pld->getObject()))
		{
			canMove = false;
			currPos.y -= pld->getSpeed();
			pld->getObject()->setState(STAYDOWN_T);
		}
		break;
	}
	currPos.x = std::roundf(currPos.x);
	currPos.y = std::roundf(currPos.y);
	pld->setPosition(currPos);
	return canMove;
}

//---------------------------------------------------------------------------//
/*
 * This method get a direction of a player, and a pointer to his object
 * Returns true if he can play the wanted move.
 */
bool GameManager::canPlayerMove(PlayerState dir, Player * pld)
{
	sf::Vector2i mapSize = m_gameMap.getGridSize();
	sf::Vector2i gridPos = m_gameMap.fixedPos(pld->getPosition());
	StaticObject * obj = nullptr;
	switch (dir)
	{
	case LEFT_T:
		if (gridPos.x - 1 < 0)
			gridPos.x++;
		obj = m_gameMap.getGridPos(gridPos.x - 1, gridPos.y);
		break;
	case RIGHT_T:
		if (gridPos.x + 1 >= mapSize.y)
			gridPos.x--;
		obj = m_gameMap.getGridPos(gridPos.x + 1, gridPos.y);
		break;
	case UP_T:
		if (gridPos.y - 1 < 0)
			gridPos.y++;
		obj = m_gameMap.getGridPos(gridPos.x, gridPos.y - 1);
		break;
	case DOWN_T:
		if (gridPos.y + 1 >= mapSize.x)
			gridPos.y--;
		obj = m_gameMap.getGridPos(gridPos.x, gridPos.y + 1);
		break;
	}
	if (dynamic_cast<Wall *>(obj))
		return false;
	return true;
}

bool GameManager::isPlayerReachBounds(PlayerState dir, Player * pld)
{
	sf::Vector2i mapSize = m_gameMap.getGridSize();
	sf::Vector2i gridPos = m_gameMap.fixedPos(pld->getPosition());
	switch (dir)
	{
	case LEFT_T:
		if (gridPos.x - 1 < 0)
			return false;
		break;
	case RIGHT_T:
		if (gridPos.x + 1 == mapSize.y)
			return false;
		break;
	case UP_T:
		if (gridPos.y - 1 < 0)
			return false;
		break;
	case DOWN_T:
		if (gridPos.y + 1 == mapSize.x)
			return false;
		break;
	}
	return true;
}

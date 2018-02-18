#pragma once
#include <SFML\Graphics\Color.hpp>
// enum of the types of an object's color in the game can be
enum Color_t
{
	RED = 1,
	GREEN,
	BLUE
};

// key-array of symbols on the level file format
static const char m_symbols[4][3] =
{ { '@', 'S' , 'W' },
{ '%', 'T' ,'G' },
{ '#', 'E' ,'D' },
{ '*', 'I' , 'K' } };

// enum of the object type
enum ObectType_t 
{
	EMPTY_BLOCK_T,
	PACMAN_T,
	DEMON_T,
	WALL_T,
	COOKIE_T
};

// enum of the cookie type
enum CookieType
{
	NORMAL_T,
	HEALTHY_T,
	POSION_T
};

// enum of the player Direction
enum PlayerState
{
	STAY_T,
	LEFT_T,
	RIGHT_T,
	UP_T,
	DOWN_T,
	STAYLEFT_T,
	STAYUP_T,
	STAYDOWN_T
};

// enum of the Menu Buttons operations on the game
enum ButtonDesc
{
	NEW_GAME_T ,
	LOAD_GAME_T,
	HELP_T,
	
	CONTINUE_T = 10,
	RESTART_LEVEL_T,
	RESTART_GAME_T,
	SAVE_GAME_T,
	
	TOGGLE_SOUND_T,
	EXIT_T
};


// menu-related setting
const sf::Color SELECTED = sf::Color::Red;
const sf::Color NOT_SELECTED = sf::Color::White;

// Game-related settings
const int LIFE = 3;			// (human) player's lives at start of game
const int SIZE1 = 30;			// size (in pixels) of each square of object
const int MAX_NAME_LEN = 10;      //  the maximum legth of the player's name
const int POSION_TIME = 7;		// timer of poison cookie
const int HEALTH_TIME = 14;		// timer of health cookie
const int COOKIE_LIMIT = 200;	// limit for cookie that can get Pacman 1 more life

const float MAX_SPEED = 2.44f;    // max speed of pacman movement in pixels/sec
const float MIN_SPEED = 0.56f;   // min speed of pacman movement in pixels/sec





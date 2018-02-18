#include "PlayerD.h"
#include <windows.h>
#include <ctime>

//---------------------------------------------------------------------------//
/*
 * Constructor of player demon
 */
PlayerD::PlayerD(sf::Vector2f newPos, sf::Color newColor)
{
	m_clock.restart();
	srand((unsigned)m_clock.getElapsedTime().asMicroseconds());
	int x = rand() % 100;

	// gice a ratio 40/60 for smart/stupid demon
	if (x < 40)
		m_character = new (std::nothrow) SmartDemon(newPos, newColor);
	else 
		m_character = new (std::nothrow) StupidDemon(newPos, newColor);

	m_character->setPosition(newPos);
	m_character->setColor(newColor);
}

//---------------------------------------------------------------------------//
/*
 *  destructor of player demon 
 */
PlayerD::~PlayerD()
{
	delete m_character;
}

//---------------------------------------------------------------------------//
/*
 *
 */
PlayerState PlayerD::setNewDirect(PlayerState last)
{
	srand((unsigned)m_clock.getElapsedTime().asMilliseconds());
	int choise;
	if ((int)m_clock.getElapsedTime().asSeconds() % 3 == 0)
		choise = 3 + rand() % 2;
	else
		choise = 1 + rand() % 2;

	if (choise == 1 || choise == 2 || choise == 3 || choise == 4)
		m_character->setSpeed(1);

	if (choise == 2 && last != LEFT_T)
		m_newD = RIGHT_T;

	else if (choise == 1 && last != RIGHT_T)
		m_newD = LEFT_T;

	else if (choise == 3 && last != DOWN_T)
		m_newD = UP_T;

	else if (choise == 4 && last != UP_T)
		m_newD = DOWN_T;

	return m_newD;
}

//---------------------------------------------------------------------------//
/*
 *
 */
Demon * PlayerD::getObject() const
{
	return dynamic_cast<Demon*>(m_character);
}

//---------------------------------------------------------------------------//
/*
 * method 1 of player demon when demon is smart 
 */
PlayerState PlayerD::smartMove(PlayerState pacmanMove)
{
	PlayerState _newD = STAY_T;
	switch (pacmanMove)
	{
	case LEFT_T:
		_newD = RIGHT_T;
		break;
	case RIGHT_T:
		_newD = LEFT_T;
		break;
	case UP_T:
		_newD = DOWN_T;
		break;
	case DOWN_T:
		_newD = UP_T;
		break;
	case STAY_T:
	case STAYLEFT_T:
	case STAYDOWN_T:
	case STAYUP_T:
		return m_newD;
		break;
	}
	return _newD;
}

//---------------------------------------------------------------------------//
/*
 * 2nd method of player demon when demon is smart 
 */
PlayerState PlayerD::smartMove2(PlayerP* p, sf::Vector2i mapSize)
{
	sf::Vector2f pacmanPlace = p->getCenter();

	sf::Vector2f currPos1 = getCenter();
	sf::Vector2i gridPos1 = { (int)(currPos1.x / SIZE1),(int)(currPos1.y / SIZE1) };
	gridPos1.x = (gridPos1.x < 0) ? 0 : (gridPos1.x >= mapSize.y) ? mapSize.y : gridPos1.x;
	gridPos1.y = (gridPos1.y < 0) ? 0 : (gridPos1.y >= mapSize.x) ? mapSize.x : gridPos1.y;

	sf::Vector2f currPos2 = pacmanPlace;
	sf::Vector2i gridPos2 = { (int)(currPos2.x / SIZE1),(int)(currPos2.y / SIZE1) };
	gridPos2.x = (gridPos2.x < 0) ? 0 : (gridPos2.x >= mapSize.y) ? mapSize.y : gridPos2.x;
	gridPos2.y = (gridPos2.y < 0) ? 0 : (gridPos2.y >= mapSize.x) ? mapSize.x : gridPos2.y;

	std::array<sf::Vector2i, 4> moves =
	{ sf::Vector2i(0, -1),      // move up
		sf::Vector2i(0, 1),     // move down
		sf::Vector2i(-1, 0),    // move left
		sf::Vector2i(1, 0)      // move right
	};

	int x = Manhaten(gridPos2, gridPos1);
	int last = x;
	PlayerState minDistSide = STAY_T;
	int upDist = Manhaten(gridPos1 + moves[0], gridPos2);
	int downDist = Manhaten(gridPos1 + moves[1], gridPos2);
	int leftDist = Manhaten(gridPos1 + moves[2], gridPos2);
	int rightDist = Manhaten(gridPos1 + moves[3], gridPos2);

	int distSide[4] = { leftDist, rightDist, upDist , downDist };

	for (int i = 0; i < 4; i++) {
		if (distSide[i] <= x)
		{
			x = distSide[i];
			minDistSide = (PlayerState)(i + 1);
		}
	}

	if (minDistSide == STAY_T)
	{
		x++;
		for (int i = 0; i < 4; i++) {
			if (distSide[i] == x)
			{
				x = distSide[i];
				minDistSide = (PlayerState)(i + 1);
			}
		}
	}
	return minDistSide;
}

//---------------------------------------------------------------------------//
/*
 * calculates distance using mahanten
 */
 int PlayerD::Manhaten(sf::Vector2i v1, sf::Vector2i v2)
 {
	 return std::abs(v1.x - v2.x) + std::abs(v1.y - v2.y);
 }

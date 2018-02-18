#pragma once
#include "StupidDemon.h"
#include "SmartDemon.h"
#include "PlayerP.h" 
#include <array>

class PlayerD : public Player
{

public:
	PlayerD(sf::Vector2f newPos = { 0,0 },
		    sf::Color newColor = sf::Color::Transparent);
	~PlayerD();

	PlayerState setNewDirect(PlayerState last); // return Demon wanted direction
	Demon* getObject() const; 
	PlayerState smartMove(PlayerState pacmanMove);
	PlayerState smartMove2(PlayerP* p, sf::Vector2i mapSize);
	int Manhaten(sf::Vector2i v1, sf::Vector2i v2);

private:
	sf::Clock m_clock;			// clock for demon moves
};


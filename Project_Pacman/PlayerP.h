#pragma once
#include "Pacman.h"
#include "Player.h"
class PlayerP: public Player
{
public:
	PlayerP(sf::Vector2f newPos, sf::Color newColor);
	~PlayerP();
	
 	PlayerState setNewDirect(PlayerState last); // get Pacman wanted direction
	void kill();					// down life for Pacman
	bool isAlive() const;		     // check if Pacman is alive
	size_t getlives() const;	     // return Pacman life 
	void addLife();					 // add Pacman life
	Pacman* getObject() const;		 // return Pacman object
	void setlife(size_t);			 // set Pacman life



private:
	size_t m_life;
};


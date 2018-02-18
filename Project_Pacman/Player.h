#pragma once
#include "Character.h"
class Player 
{
public:
	Player();
	void draw(sf::RenderWindow &) const; // draw character on window
	void playMove(PlayerState last); // in charge of character move 
	// set character new direction (Virtual) 
	virtual PlayerState setNewDirect(PlayerState last) = 0;
	PlayerState getNew(); // return wanted direction
	void setStayDirect(PlayerState state); // set character to Stay in his direction
	Character* getObject() const; // get the character type , Pacman|Demon
	PlayerState getDirection() const; // return character current direction
	sf::Vector2f getCenter() const; // return character center
	void setOrigin(sf::Vector2f newPos); // set character origin
	sf::Vector2f getPosition() const; // return character position
	void setPosition(sf::Vector2f newPlace); // set character position by vector
	void setPosition(float x, float y); // // set character position by x & y
	float getSpeed() const; // return Player Speed
	void setSpeed(float speed); // set Player Speed
	void setPlayer(sf::Vector2f newPos, sf::Color newColor); // set up Player
	~Player();

protected:
	PlayerState m_newD;
	Character * m_character;
};


#pragma once
#include "StaticObject.h"
#include "PlayerP.h"
#include "PlayerD.h"
#include <vector>

class Board
{
public:
	Board();
	~Board();
	// load all object from file 
	bool loadFromFile(const std::string fileName,
		PlayerP*& _player, std::vector<PlayerD*>&);
	// display the grid on the screen
	void display(sf::RenderWindow & _window) const;
	// return the object from location in the grid 
	StaticObject* getGridPos(int row, int col) const;
	// clean the object from grid
	void clear(int, int);
	sf::Vector2i getGridSize() const;			//return grid size
	void resetCookies();						// reset the cookie member
	void addCookies(int sum);			 // add cookie for the cookie member
	int cookiesLeft() const;					 // return the cookie member
	sf::Vector2i fixedPos(sf::Vector2f) const;  // returns object grid pos

private:
	int m_Cookies;
	std::vector < std::vector <StaticObject*>> m_grid; // game's Data Structure 
	sf::Vector2i m_mapSize;
	
	/***	 help functions		***/
	sf::Vector2i getSignPos(char ch) const;  // return object color/type
	void File2Grid(std::ifstream &,			// load file to the grid
		           PlayerP*&, std::vector<PlayerD*>&);
	void EmptyBoard();				  // clean the grid from object (for D-tor)
	bool inRange(int i, int j) const;			// return if indexes are good
};


#include "Board.h"
#include "Pacman.h"
#include "Wall.h"
#include "Cookie.h"
#include "Demon.h"
#include <fstream>


//---------------------------------------------------------------------------//
/*
 * Constructor of Board Object, defines a new Empty board with no cookies
 */
Board::Board()
	:m_Cookies(0)
{ 
}

//---------------------------------------------------------------------------//
/*
 * Destructor of of Board Object, emties the board and clean the memory the
 * object used
 */
Board::~Board()
{
	EmptyBoard();
}

//---------------------------------------------------------------------------//
/*
 * This method gets a file descriptor , pointer to Player and poiter to the 
 * Demon-player(s).
 * load the the level map from the file into thr game.
 */
bool Board::loadFromFile(const std::string fileName,
	                     PlayerP*& _player,
	                     std::vector <PlayerD*>&  p_demons)
{
	std::ifstream file;
	EmptyBoard();			// clean before new changes

	file.open(fileName, std::ios_base::binary);
	if (!file.is_open())
		return false; 

	// clean old data of Players
	for (int i = 0; i < p_demons.size(); i++)
		if (p_demons[i] != nullptr)
			delete p_demons[i];

	if (_player != nullptr)
		delete _player;

	File2Grid(file, _player, p_demons);
	file.close();
	return true;
}

//---------------------------------------------------------------------------//
/*
 * This method gets a file descriptor , pointer to Player and pointer to the
 * Demon-player(s).
 * update the level map from the file into the game, updates also the 
 * characteristics of the Players (Pacman and Demon).
 */
void Board::File2Grid(std::ifstream & file,
				      PlayerP*& p,
	                  std::vector <PlayerD*> & p_demons)
{
	p_demons.resize(0);					// clear old vector before using
	file >> m_mapSize.x >> m_mapSize.y;
	file.get();
	file.get();
	std::vector<StaticObject*> tempCells; // help-vector for pushing to grid
	PlayerD * tmp_pl_d = nullptr;
	for (int i = 0; i < m_mapSize.x; i++)
	{
		for (int j = 0; j < m_mapSize.y; j++)
		{
			char currPosSign = file.get();
			sf::Vector2f currPos = sf::Vector2f(j * 30.f, i *30.f + 60);
			StaticObject* tmp = nullptr;
			Demon * tmp_d = nullptr;

			sf::Vector2i sign_t = getSignPos(currPosSign);
			int sign_color = sign_t.y;
			int sign_type = sign_t.x;
			sf::Color object_color;
			
			switch (sign_color)
			{
			case RED: object_color = sf::Color::Red; break;
			case GREEN: object_color = sf::Color::Green; break;
			case BLUE: object_color = sf::Color::Blue; break;
			}

			switch (sign_type)
			{
			case PACMAN_T:
				p = new PlayerP(currPos, object_color);
				break;
			case DEMON_T:
				tmp_pl_d = new PlayerD(currPos, object_color);
				p_demons.push_back(tmp_pl_d);
				break;
			case WALL_T:
				tmp = new Wall(currPos, object_color);
				break;
			case COOKIE_T:
				tmp = new Cookie(currPos, object_color);
				addCookies(1);
				break;
			case EMPTY_BLOCK_T:
				break;
			}
			tempCells.push_back(tmp);
		}
		file.get();
		file.get();
		m_grid.push_back(tempCells);
		tempCells.clear();
	}
}

//---------------------------------------------------------------------------//
/*
 * This method gets a render window.
 * displays the level map on this window.
 */
void Board::display(sf::RenderWindow & _window) const
{
	for (int i = 0; i < m_grid.size(); ++i)
		for (int j = 0; j < m_grid[i].size(); ++j)
			if ((m_grid[i][j]) != nullptr)
				(m_grid[i][j])->draw(_window);
}

//---------------------------------------------------------------------------//
/*
 * This method gets 2 indexes.
 * return the Static object (if exist) on a particular cell (row, col)
 */
StaticObject* Board::getGridPos(int row, int col) const
{
	if (inRange(row, col))
		return (m_grid[col][row]);
	return nullptr;				// index(s) are wrong
}

//---------------------------------------------------------------------------//
/*
 * This method gets 2 indexes.
 * clear (if exist) the object on a particular cell (i, j)
 */
void Board::clear(int i, int j)
{
	if (inRange(i, j))
	{
		delete m_grid[i][j];
		m_grid[i][j] = nullptr;
	}
}

//---------------------------------------------------------------------------//
/*
 * This method returns the game's map size by 2-dim vector.
 * when x = num of rows, y = num of cols.
 */
sf::Vector2i Board::getGridSize() const
{
	return m_mapSize;
}

//---------------------------------------------------------------------------//
/*
 * This method sets the number of game's map cookies to 0.
 */
void Board::resetCookies()
{
	m_Cookies = 0;
}

//---------------------------------------------------------------------------//
/*
 * This method get a number of cookies to add / subtract
 * updates the number of game's map cookies by this number.
 */
void Board::addCookies(int sum)
{
	m_Cookies += sum;
}

//---------------------------------------------------------------------------//
/*
 * This method return the a number of cookies exist on the map
 * therefore, the number of cookies the player hace to eat.
 */
int Board::cookiesLeft() const
{
	return m_Cookies;
}

//---------------------------------------------------------------------------//
/*
 * This method gets the char presets an object on the map (Wall/ Cookie)
 * return a vector presents the object's type and his color.
 * x = object's type, y = object's color
 */
sf::Vector2i Board::getSignPos(char ch) const
{
	if (ch == EMPTY_BLOCK_T)
		return sf::Vector2i(0, 0);
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 3; j++)
			if (m_symbols[i][j] == ch)
				return sf::Vector2i(i + 1, j + 1);

	return sf::Vector2i(-1, -1);
}

//----------------------------------------------------------------------------//
/*
 *	This method get a pointer to a Player object.
 *	Returns Fixed the player position to as related to the grid of map.
 */
sf::Vector2i Board::fixedPos(sf::Vector2f currPos) const
{
	sf::Vector2i gridPos = { (int)std::round((currPos.x / SIZE1)),
		(int)std::round(((currPos.y - 2*SIZE1) / SIZE1)) };

	gridPos.x = (gridPos.x < 0) ? 0 : (gridPos.x >= m_mapSize.y) ? m_mapSize.y : gridPos.x;
	gridPos.y = (gridPos.y < 0) ? 0 : (gridPos.y >= m_mapSize.x) ? m_mapSize.x : gridPos.y;
	return gridPos;
}

//---------------------------------------------------------------------------//
/*
*
*/
void Board::EmptyBoard()
{
	for (unsigned i = 0; i < m_grid.size(); i++)
	{
		for (unsigned j = 0; j < m_grid[i].size(); j++)
			if (m_grid[i][j] != nullptr)
				delete m_grid[i][j];
		m_grid[i].clear();
	}
	m_grid.clear();
}


//----------------------------------------------------------------------------//
/*
*	This method get 2 indexes
*	Returns true if they presents a valid cell on the grid
*/
bool Board::inRange(int i, int j) const
{
	return (i >= 0 && i < m_mapSize.x) && (j >= 0 && j < m_mapSize.y);
}

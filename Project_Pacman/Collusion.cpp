#include "Collusion.h"
#include "Wall.h"

//---------------------------------------------------------------------------//
/*
 * This method checks if Pacman is collided with a ghost
 */
bool Collusion::isPacmanCollidedGhost(Pacman & pacman, Demon * demon)
{
	sf::Sprite a_pacman = pacman.getObject();
	sf::Sprite a_demon = demon->getObject();
	return AABBCollision(a_pacman.getGlobalBounds(), a_demon.getGlobalBounds());
}

//---------------------------------------------------------------------------//
/*
 * This method checks if Pacman is collided with a cookie, means he ate it 
 */
bool Collusion::isPacmanCollidedCookie(Pacman & pacman, StaticObject * cookie)
{
	if (dynamic_cast<Cookie *>(cookie)) 
	{
		sf::Sprite a_pacman = pacman.getObject();
		if (a_pacman.getGlobalBounds().contains(cookie->getCenter()))
			return true;
	}
	return false;
}

//---------------------------------------------------------------------------//
/*
 * This method checks if a charcter collided with a static object
 */
bool Collusion::CheckCollusion(StaticObject * obj, const Character * charcter)
{
	if (dynamic_cast<Wall *>(obj))
	{
		sf::Sprite a_charcter = charcter->getObject();
		sf::Sprite obj1 = obj->getObject();
		return AABBCollision(a_charcter.getGlobalBounds(), obj1.getGlobalBounds());
	}
	return false;
}

//---------------------------------------------------------------------------//
/*
 * This method perform the A A B B collusion algorithm
 * return true if the the 2 objects collided, else returns false
 */
bool Collusion::AABBCollision(const sf::FloatRect & obj1, const sf::FloatRect & currOBJ)
{
	return std::abs(obj1.left - currOBJ.left) * 2 < (obj1.width + currOBJ.width - 1) &&
		std::abs(obj1.top - currOBJ.top) * 2 < (obj1.height + currOBJ.height - 1);
}

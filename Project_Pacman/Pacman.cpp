#include "Pacman.h"


//---------------------------------------------------------------------------//
/*
 * Constructor of the Pacman object in the game, defines his initial settings
 * as speed , direction and animation
 */ 
Pacman::Pacman(const sf::Vector2f & _pos, sf::Color _color)
{
	m_color = _color;
	m_speed = 1.f;
	m_key = STAY_T;
	m_texture.loadFromFile("Image\\pacman.png");
	m_textureDown.loadFromFile("Image\\pacmanDown.png");
	m_textureUp.loadFromFile("Image\\pacmanUp.png");

	m_body.setTexture(m_texture);
	m_body.setColor(m_color);
	m_body.setPosition((sf::Vector2f) _pos);
}

//---------------------------------------------------------------------------//
/*
 *  This method gets a render window.
 *  draws the Pacman on this window, according to his direction
 */
void Pacman::draw(sf::RenderWindow& app) const
{
	sf::Sprite copy_body;// = m_body;
 	copy_body.setColor(this->m_color);
 	copy_body.setPosition(this->m_body.getPosition());

	// define direction right
	switch (m_key)
	{
	case STAY_T:
	case LEFT_T:
	case RIGHT_T:
	case STAYLEFT_T:
		copy_body.setTexture(m_texture);
		break;
	case UP_T:
	case STAYUP_T:
		copy_body.setTexture(m_textureUp);
		break;
	case DOWN_T:
	case STAYDOWN_T:
		copy_body.setTexture(m_textureDown);
		break;
	}

	// define face right
	switch (m_key)
	{
	case STAY_T:
	case RIGHT_T:
		copy_body.setTextureRect(sf::IntRect(0, 0, SIZE1, SIZE1));
		break;
	case LEFT_T:
	case UP_T:
	case DOWN_T:
	case STAYLEFT_T:
	case STAYUP_T:
	case STAYDOWN_T:
		copy_body.setTextureRect(sf::IntRect(SIZE1, 0, -SIZE1, SIZE1));
		break;
	default:
		copy_body.setTexture(m_texture);
		copy_body.setTextureRect(sf::IntRect(0, 0, SIZE1, SIZE1));
		break;
	}
	
	app.draw(copy_body);
}

//---------------------------------------------------------------------------//
/*
 *  This method defines the movement of the Pacman on screen
 */
void Pacman::move()
{
	sf::Vector2f update;			// keeps the updated movement
	switch (m_key)
	{
	case RIGHT_T:
		update = sf::Vector2f(m_speed, 0.f);
		break;
	case LEFT_T:
		update = sf::Vector2f(-m_speed, 0.f);
		break;
	case UP_T:
		update = sf::Vector2f(0.f, -m_speed);
		break;
	case DOWN_T:
		update = sf::Vector2f(0.f, m_speed);
		break;
	case STAY_T:
	case STAYUP_T:
	case STAYDOWN_T:
	case STAYLEFT_T:
		update = sf::Vector2f(0, 0);
		break;
	}

	sf::Vector2f currPos = m_body.getPosition();
	m_body.setPosition(currPos + update);

}

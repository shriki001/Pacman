#pragma once
#include "StaticObject.h"

class Cookie : public StaticObject
{
public:
	Cookie();
	Cookie(const sf::Vector2f & _pos, const sf::Color& _color);
	void draw(sf::RenderWindow& app)const;// draw cookie on screen
	CookieType getCookieType() const; // return Healthy|Poison|normal 
	void setCookieType(const sf::Color &_color); //set color of cookie type
	sf::Vector2f getCenter() const; //get center of the cookie
	sf::Vector2f getPosition() const; //get the position of the  cookie
	
private:
	enum CookieType m_type;			// keep cookie type
	sf::Texture m_texture;
};


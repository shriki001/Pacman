#pragma once
#include "Demon.h"


class SmartDemon :public Demon
{
	
public:
	SmartDemon(const sf::Vector2f & _pos, sf::Color _color);
	void SmartMove(PlayerState dir);
	void move();
	double Manhaten(sf::Vector2f,sf::Vector2f);

private:
	PlayerState m_dir;
};


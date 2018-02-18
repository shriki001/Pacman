#pragma once
#include <SFML/Graphics.hpp>

const int K = 4;

class ImageManger
{
public:
	ImageManger();
	~ImageManger();
	sf::Texture& loadWallImage();

private:
	sf::Texture m_textures[K]; // img texture
	sf::Sprite m_sprites[K]; // img files 
};


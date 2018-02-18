#include "ImageManger.h"



ImageManger::ImageManger()
{
	m_textures[0].loadFromFile("Image\\pacman.png");
	m_textures[1].loadFromFile("Image\\wall.png");
	m_textures[2].loadFromFile("Image\\cookie.png");
	m_textures[3].loadFromFile("Image\\demon.png");

	for (int i = 0; i < K; i++)
		m_sprites[i].setTexture(m_textures[i]);
}


ImageManger::~ImageManger()
{
}

sf::Texture& ImageManger::loadWallImage()
{
	sf::Texture t;
	t = m_textures[1];
	return t;
}

#pragma once
#include <SFML/Audio.hpp>

const int N = 8;
class SoundManager
{
public:
	SoundManager();

	void playMenuPass(); 
	void playMenuOk();
	void playGameOver();
	void playGamePause();
	void playLoseLife();
	void playIntro();
	void playAteCookie();
	void playWin();
	void Mute(); // toggle sound
	bool isSoundOn();

private:
	sf::SoundBuffer m_audio_buff[N]; // sound buffer
	sf::Sound m_audio[N]; // sound files 
	bool m_Mute;
};


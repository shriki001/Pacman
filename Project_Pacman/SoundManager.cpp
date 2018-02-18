#include "SoundManager.h"

//---------------------------------------------------------------------------//
/*
 *  
 */
SoundManager::SoundManager()
	:m_Mute(false)
{
	m_audio_buff[0].loadFromFile("Sound\\menu_pass.wav");
	m_audio_buff[1].loadFromFile("Sound\\drip.wav");
	m_audio_buff[2].loadFromFile("Sound\\game_over.wav");
	m_audio_buff[3].loadFromFile("Sound\\game_pause.wav");
	m_audio_buff[4].loadFromFile("Sound\\intro.wav");
	m_audio_buff[5].loadFromFile("Sound\\lose_life.wav");
	m_audio_buff[6].loadFromFile("Sound\\menu_ok.wav");
	m_audio_buff[7].loadFromFile("Sound\\win.wav");
	for (int i = 0; i < N; i++)
		m_audio[i].setBuffer(m_audio_buff[i]);
}

//---------------------------------------------------------------------------//
/*
 *
 */
void SoundManager::playMenuPass()
{
	if (!m_Mute) 
		m_audio[0].play();
}

//---------------------------------------------------------------------------//
/*
 *
 */
void SoundManager::playMenuOk()
{
	if (!m_Mute)
		m_audio[6].play();
}

//---------------------------------------------------------------------------//
/*
 *
 */
void SoundManager::playGameOver()
{
	if (!m_Mute)
		m_audio[2].play();
}

//---------------------------------------------------------------------------//
/*
 *
 */
void SoundManager::playGamePause()
{
	if (!m_Mute)
		m_audio[3].play();
}

//---------------------------------------------------------------------------//
/*
 *
 */
void SoundManager::playLoseLife()
{
	if (!m_Mute)
		m_audio[5].play();
}

//---------------------------------------------------------------------------//
/*
 *
 */
void SoundManager::playIntro()
{
	if (!m_Mute)
		m_audio[4].play();
}

//---------------------------------------------------------------------------//
/*
 *
 */
void SoundManager::playAteCookie()
{
	if (!m_Mute)
		m_audio[1].play();
}

//---------------------------------------------------------------------------//
/*
 *
 */
void SoundManager::playWin()
{
	if (!m_Mute)
		m_audio[7].play();
}

//---------------------------------------------------------------------------//
/*
 *
 */
void SoundManager::Mute()
{
	m_Mute = !m_Mute;
}

//---------------------------------------------------------------------------//
/*
 *
 */
bool SoundManager::isSoundOn()
{
	return !m_Mute;
}


#pragma once
#include "gameText.h"
#include <windows.h>

void openMsgWin(std::string WindowTitle, std::string WindowMsgTxt, sf::Color color);
bool openAskWin(std::string WindowTitle);
void makeWindowOnTop(sf::RenderWindow& window);

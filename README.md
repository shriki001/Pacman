Object Oriented Programming: 2018 a

End of semester Project: Michael Shriki, Kfir Matityahu

This program is a Pacman Game

=================================================================

Design:
-----------------------------------------------------------------

PACMAN:

Role: The character that in the control of the user, starts with 3 lives.


DEAMON:
 
Role: The character that in the control of the "CPU", the game decides to make Smart Demon or Stupid Demon. 

(40% for the Smart and 60% for Stupid). 


WALL:
 
Role: A perimeter of the map, used as an obstacle, which the Pacman and Demon can't go through it.


COOKIE:

Role: The Player's food. Player must to eat all of the cookies in the level to pass to the next level.

Green Cookie UP Player speed for 14 sec, Blue Cookie DOWN Player speed for 7 sec

=================================================================

Levels:

The levels must be in the following Directory: 

Pacman/Levels and the name must be lvl(number).txt (e.g. lvl1.txt), (number) represent the level number that you want.

To make your own levels for this game you can use the Map Editor that provide with the installer.

Otherwise: Inside the .txt file you must give the size of the map in one line e.g. 20 20 for 20X20 map. 

(the game come with 4 levels by default).


Files:
-----------------------------------------------------------------

Board.h & Board.cpp

The manager of reading levels from file and create the objects.

Button.h & Button.cpp

In charge of create new button for the menus.

Character.h & Character.cpp

Abstract class for make object (Pacman | Demon) in the Game.

Collusion.h & Collusion.cpp

In charge of all the collusion between object and Static object in the game. 

Cookie.h & Cookie.cpp

Class for make a new Cookie texture in the game. 

Demon.h & Demon.cpp

Abstract class for make a Demon in the game.

EndGameMenu.h & EndGameMenu.cpp

In charge of the end of the game.

GameInfo.h & GameInfo.cpp

In charge of all the info in the running game (Lives | Score | Player name etc.).

GameManager.h & GameManager.cpp

The engine of the game, in charge of all character movements, start the game and menu manager.

gameText.h

Struct to load texture for the game.

ImageManger.h & ImageManger.cpp

In charge of load all game images

main.cpp

The main Game that we execute.

Menu.h & Menu.cpp

Abstract class for the game menus.

Pacman.h & Pacman.cpp

Class for make a new Pacman texture in the game.

PauseMenu.h & PauseMenu.cpp

In charge of the menu in the running game.

Player.h & Player.cpp

Abstract class for all moveable object.

PlayerD.h & PlayerD.cpp

In charge of demon movement (Stupid and Smart). 

PlayerP.h & PlayerP.cpp

In charge of Pacman movement.

Settings.h: 

Defines of all the Characters/Keys/Const/enum of the game.

SmartDemon.h & SmartDemon.cpp

In charge of the Smart Demon in the game.

SoundManager.h & SoundManager.cpp

In charge of all the sound in the game include mute and unmute.

StartMenu.h & StartMenu.cpp

In charge of the start screen menu in starting game.

StaticObject.h & StaticObject.cpp

Abstract class that in charge of the game static object (Wall | Cookie).

StupidDemon.h & StupidDemon.cpp

In charge of the Stupid Demon in the game.

UtilWindows.h & UtilWindows.cpp

In charge of the messages for the Player in the game.

Wall.h & Wall.cpp

Class for make a new Wall texture in the game.

=================================================================

Remarkable Algorithms:
-----------------------------------------------------------------

All movement for the movable object in the game e.g. move in Axis, teleports and bounds

Smart Demon movement

================================================================

Data Structures:
-----------------------------------------------------------------

We use C++ Vector for the Game Map

=================================================================

Known Bugs:

None.

=================================================================

Other notes:

Every time that Pacman ate 200 Cookie he got I more life.

Cheats:

Key 'S' - skip to the next Level

Key 'L' - add one more life to player

=================================================================

Memory Leak State: 
no memory leak

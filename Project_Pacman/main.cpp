#ifdef _DEBUG
#pragma comment(lib, "sfml-main-d.lib")
#elif defined(NDEBUG)
#pragma comment(lib, "sfml-main.lib")
#else
#error "Unrecognized configuration!"
#endif

#include "GameManager.h"
int main()
{
	GameManager Newgame;
	Newgame.run();


	return EXIT_SUCCESS;
}
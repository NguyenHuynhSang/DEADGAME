#include "Game.h"

CGame * CGame::__instance = NULL;

CGame * CGame::GetInstance()
{
	if (__instance == NULL) __instance = new CGame();
	return __instance;
}

CGame::CGame()
{
}


CGame::~CGame()
{
}

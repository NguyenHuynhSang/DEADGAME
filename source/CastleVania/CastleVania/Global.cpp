#include "Global.h"
#include<Windows.h>
Global * Global::__instance = NULL;

Global * Global::GetInstance()
{
	if (__instance == NULL) __instance = new Global();
	return __instance;
}

Global::Global()
{
	SIMON_WALKING_TEST = 0;
}


Global::~Global()
{
}

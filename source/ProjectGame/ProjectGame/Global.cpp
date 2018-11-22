#include "Global.h"

CGlobal * CGlobal::__instance = NULL;

CGlobal * CGlobal::GetInstance()
{
	if (__instance == NULL) __instance = new CGlobal();
	return __instance;
}

CGlobal::CGlobal()
{
}


CGlobal::~CGlobal()
{
}

#include "Camera.h"


CCamera * CCamera::__instance = NULL;

CCamera *CCamera::GetInstance()
{
	if (__instance == NULL) __instance = new CCamera();
	return __instance;
}
CCamera::CCamera()
{
	CamX = 0;
	CamY = 0;
	isCamMove = false;
}


CCamera::~CCamera()
{
}

#include "Camera.h"


CCamera * CCamera::__instance = NULL;

CCamera *CCamera::GetInstance()
{
	if (__instance == NULL) __instance = new CCamera();
	return __instance;
}
bool CCamera::autoCamera(float X)
{
	if (CamX >= X)
	{
		return true;
	}
	endautoTime = GetTickCount();
	if (isauto == true)
	{
		isauto = false;
		startautoTime = GetTickCount();
	}

	CamX += 2;
	
	return false;

}
CCamera::CCamera()
{
	isauto = true;
	CamX = 0;
	CamY = 0;
	isCamMove = false;
}


CCamera::~CCamera()
{
}

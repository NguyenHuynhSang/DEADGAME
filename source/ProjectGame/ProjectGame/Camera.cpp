#include "Camera.h"


CCamera * CCamera::__instance = NULL;

CCamera *CCamera::GetInstance()
{
	if (__instance == NULL) __instance = new CCamera();
	return __instance;
}
void CCamera::autoCamera(float X)
{
	endautoTime = GetTickCount();
	if (isauto == true)
	{
		isauto = false;
		startautoTime = GetTickCount();
	}
	if (endautoTime - startautoTime<CAM_AUTO_TIME)
	{
		CamX += 2;
	}


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

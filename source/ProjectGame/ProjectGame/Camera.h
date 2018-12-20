#pragma once
#include<Windows.h>
#include<d3d9.h>
#include<d3dx9.h>
#include"Global.h"
class CCamera
{
	float CamX;
	float CamY;

public:
	static CCamera * __instance;
	void setCamera(float x, float y) { CamX = x; CamY = y; };
	void getCamera(float &x, float &y) { x = CamX; y = CamY; };
	float getCamX() { return CamX; }
	static CCamera * GetInstance();
	void ResetCam() { CamX = 0; CamY = 0; };
	void formatCamera() {}
	float getVPWidth() { return CamX + SCREEN_WIDTH; }
	float getVPHeight() { return CamY + SCREEN_HEIGHT; }
	bool isCamMove;
	CCamera();
	~CCamera();
};


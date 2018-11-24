#pragma once
#include<Windows.h>
#include<d3d9.h>
#include<d3dx9.h>
class CCamera
{
	float CamX;
	float CamY;

public:
	static CCamera * __instance;
	void setCamera(float x, float y) { CamX = x; CamY = 0; };
	void getCamera(float &x, float &y) { x = CamX; y = CamY; };
	static CCamera * GetInstance();
	void formatCamera() {
	
	}
	bool isCamMove;
	CCamera();
	~CCamera();
};


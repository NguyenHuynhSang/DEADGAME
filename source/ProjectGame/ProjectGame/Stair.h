#pragma once
#include"GameObject.h"

#define ID_TEX_STAIR 21
#define STAIR_BBOX_WIDTH  32
#define STAIR_BBOX_HEIGHT 32
class CStair:public CGameObject
{
public:
	bool beginStair = false;
	virtual void Render();
	virtual void LoadResource();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	CStair();
	~CStair();
};


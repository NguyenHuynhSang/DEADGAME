#pragma once
#include "GameObject.h"


#define WHIP_BBOX_WIDTH 20
#define WHIP_BBOX_HEIGHT 60
#define ID_TEX_WHIP   55
#define WHIP_RED 0
#define WHIP_BLUE 1
#define WHIP_WHITE 2


class CWhip :public CGameObject
{

public:
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	void setnx(float nx) { this->nx = nx; }
	void SetPosition(int x1, int y1) { x = x1; y = y1; };
	CWhip();
	~CWhip();
};


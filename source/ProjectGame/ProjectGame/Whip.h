#pragma once
#include "GameObject.h"


#define WHIP_BBOX_WIDTH 72
#define WHIP_BBOX_HEIGHT 12
#define ID_TEX_WHIP   55
#define WHIP_RED 0
#define WHIP_BLUE 1
#define WHIP_WHITE 2
#define ID_WHIP_ANI 555

class CWhip :public CGameObject
{

public:
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* co);
	void setnx(float nx) { this->nx = nx; }
	void SetPosition(int x1, int y1) { x = x1; y = y1; };
	CWhip();
	~CWhip();
};


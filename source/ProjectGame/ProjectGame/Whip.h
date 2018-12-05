#pragma once
#include "GameObject.h"


#define WHIP_BBOX_WIDTH 42
#define WHIP_BBOX_HEIGHT 15

#define WHIP_BLUE_BBOX_WIDTH 42 
#define WHIP_BLUE_BBOX_HEIGHT 12 


#define WHIP_RED_BBOX_WIDTH 73 
#define WHIP_RED_BBOX_HEIGHT 12 



#define ID_TEX_WHIP   55
#define WHIP_STATE_WHITE 0
#define WHIP_STATE_BLUE 1
#define WHIP_STATE_RED 2
#define WHIP_NOLMAL_ANI_ID 555
#define WHIP_BLUE_ANI_ID 556
#define WHIP_RED_ANI_ID 557

#define WHIP_DELAY_TIME 96


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


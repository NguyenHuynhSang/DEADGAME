#pragma once
#include"GameObject.h"

#define BAT_FLYING_SPEED_X 0.13f;
#define BAT_FLYING_SPEED_y 0.13f;			


#define BAT_BBOX_WIDTH 32
#define BAT_BBOX_HEIGHT 32

#define BAT_STATE_IDLE   0
#define BAT_STATE_FLY    100


#define BAT_ANI_IDLE     0
#define BAT_ANI_FLY      1

class CBat:public CGameObject
{
public:
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render();
	virtual void LoadResource();
	CBat();
	~CBat();
};


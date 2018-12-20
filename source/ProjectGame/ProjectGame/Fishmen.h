#pragma once
#include "GameObject.h"

#define FISHMAN_GRAVITY	       0.0018f
#define FISHMAN_WALKING_SPEED  0.2f
#define FISHMAN_JUMP_SPEED_Y   0.8f

#define FISHMAN_BBOX_WIDTH 32
#define FISHMAN_BBOX_HEIGHT 64

#define FISHMAN_STATE_JUMP    0
#define FISHMAN_STATE_WALKING 100
#define FISHMAN_STATE_FIRE    200


#define FISHMAN_ANI_JUMP    0
#define FISHMAN_ANI_WALKING 1
#define FISHMAN_ANI_FIRE    2



class CFishmen:public CGameObject
{
public:
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render();
	virtual void LoadResource();
	bool isEnable = false;
	void setNx(float xx) { nx = xx; };
	CFishmen();
	~CFishmen();
};


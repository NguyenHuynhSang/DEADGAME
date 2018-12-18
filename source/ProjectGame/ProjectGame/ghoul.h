#pragma once
#include "GameObject.h"

#define GHOUL_WALKING_SPEED 0.13f;

#define GHOUL_BBOX_WIDTH 30
#define GHOUL_BBOX_HEIGHT 60
#define GHOUL_BBOX_HEIGHT_DIE 9

#define GHOUL_STATE_WALKING 100
#define GHOUL_STATE_DIE 200

#define GHOUL_ANI_WALKING 0
#define GHOUL_ANI_DIE 1

class CGhoul : public CGameObject
{
	
public:
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render();
	virtual void LoadResource();
	virtual void SetState(int state);
	CGhoul();
};
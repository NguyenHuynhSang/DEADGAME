#pragma once
#include"GameObject.h"

#define ID_TEX_DAGGER

#define DAGGER_BBOX_WIDTH 10
#define DAGGER_BBOX_HEIGHT 10

#define DAGGER_SPEED 0.2f

class CDagger:public CGameObject
{
public:
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* co);

	CDagger();
	~CDagger();
};


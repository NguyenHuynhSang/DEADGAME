#pragma once
#include"GameObject.h"
#include"Textures.h"
#define ID_TEX_DAGGER

#define DAGGER_BBOX_WIDTH 32
#define DAGGER_BBOX_HEIGHT 18

#define DAGGER_SPEED 0.3f

class CDagger:public CGameObject
{
public:
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* co);
	void setNx(float nx){this->nx=nx;}
	virtual void LoadResource();
	CDagger();
	~CDagger();
};


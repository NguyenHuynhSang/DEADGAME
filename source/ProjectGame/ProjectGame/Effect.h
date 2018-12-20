#pragma once
#include"GameObject.h"

#define EFFECT_EXPLOSION 0
#define EFFECT_ETC 1


#define EFFECT_STATE_PLAY 100
#define EFFECT_STATE_REMOVE 200



class CEffect:public CGameObject
{
public:
	bool isRemove = false;
	void setState(int st) { state = st; };
	virtual void LoadResource();
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	CEffect();
	~CEffect();
};


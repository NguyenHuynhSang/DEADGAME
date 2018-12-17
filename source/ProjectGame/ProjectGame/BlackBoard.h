#pragma once
#include"GameObject.h"

#define ID_TEX_BLACKBOARD 98

class CBlackBoard:public CGameObject
{

	static CBlackBoard * __instance;
public:
	virtual void Render();
	virtual void LoadResource();
	
	static CBlackBoard * GetInstance();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	CBlackBoard();
	~CBlackBoard();
};


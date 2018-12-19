#pragma once
#include "GameObject.h"

#define BRICK_BBOX_WIDTH  32
#define BRICK_BBOX_HEIGHT 32

#define BRICK_STATE_OLDFACTION 0
#define BRICK_STATE_MODERN 1


class CBrick : public CGameObject
{
public:
	bool panJump = false;
	virtual void Render();
	virtual void LoadResource();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	CBrick();
};
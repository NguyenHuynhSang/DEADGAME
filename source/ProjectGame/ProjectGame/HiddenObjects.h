#pragma once
#include"GameObject.h"

#define HO_STATE_STAIR_TOP 100
#define HO_STATE_STAIR_BOTTOM 200

class CHiddenObjects:public CGameObject
{
	int _width;
	int _height;
public:
	void setBoundBox(float w, float h) { _width = w; _height = h; }
	virtual void Render();
	virtual void LoadResource();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	CHiddenObjects();
	~CHiddenObjects();
};


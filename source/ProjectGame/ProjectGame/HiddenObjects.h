#pragma once
#include"GameObject.h"

#define HO_STATE_STAIR_TOP 100
#define HO_STATE_STAIR_BOTTOM 200
#define HO_STATE_GROUND    300
class CHiddenObjects:public CGameObject
{
	int _width;
	int _height;

	int stairState = 0;// 1 2 3 4 <==> upleft, upright, down l, down r
public:
	void setBoundBox(float w, float h) { _width = w; _height = h; }
	virtual void Render();
	void setStairState(float s) { stairState = s; }
	int getStairState() { return stairState; }
	virtual void LoadResource();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	CHiddenObjects();
	~CHiddenObjects();
};


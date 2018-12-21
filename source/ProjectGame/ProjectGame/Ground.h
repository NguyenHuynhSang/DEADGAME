#pragma once
#include"GameObject.h"
class CGround:public CGameObject
{
	int _width;
	int _height;

public:
	void setBoundBox(float w, float h) { _width = w; _height = h; }
	virtual void Render();
	virtual void LoadResource();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	CGround();
	~CGround();
};


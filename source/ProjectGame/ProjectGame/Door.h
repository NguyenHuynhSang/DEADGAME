#pragma once
#include"GameObject.h"



#define DOOR_STATE_BIGDOOR 0
#define DOOR_STAITE_SMAILDOOR 100

#define DOOR_ANI_SMAILDOOR  0
#define DOOR_ANI_BIGDOOR   1


#define DOOR_BBOX_HEIGHT 96
#define DOOR_BBOX_WIDTH 16

#define BDOOR_BBOX_HEIGHT 288
#define BDOOR_BBOX_WIDTH 96

class CDoor:public CGameObject
{
public:
	virtual void Render();
	virtual void LoadResource();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	CDoor();
	~CDoor();
};


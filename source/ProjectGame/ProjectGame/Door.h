#pragma once
#include"GameObject.h"


#define DOOR_STATE_HIDDEN 100

#define DOOR_BBOX_HEIGHT 32
#define DOOR_BBOX_WIDTH 32

class CDoor
{
public:
	virtual void LoadResource();
	CDoor();
	~CDoor();
};


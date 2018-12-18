#pragma once
#include"GameObject.h"

#define PANTHER_GRAVITY			0.002f
#define PANTHER_JUMP_SPEED_Y		0.4f
#define PANTHER_JUMP_SPEED_X        0.4f
#define PANTHER_WALKING_SPEED		0.2f 
#define PANTHER_STATE_LIEDOWN           0
#define PANTHER_STATE_RUNNING_LEFT    100
#define PANTHER_STATE_RUNNING_RIGHT   200
#define PANTHER_STATE_JUMPING         300
#define PANTHER_STATE_DIE             999

#define PANTHER_ANI_LIEDOWN 0
#define PANTHER_ANI_RUNNING 1
#define PANTHER_ANI_JUMPPING 2

#define PANTHER_BBOX_WIDTH          50
#define PANTHER_BBOX_HEIGHT         32



class CPanther:public CGameObject
{
public:
	bool isJumpping=false;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render();
	void setNx(float xx) { nx = xx; };
	virtual void LoadResource();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	CPanther();
	~CPanther();
};


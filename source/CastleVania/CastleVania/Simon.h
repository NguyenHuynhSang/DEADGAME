#pragma once
#include"Objects.h"

#define SIMON_WALKING 0.2f
#define SIMON_JUMP_SPEED_Y 0.2f
#define SIMON_JUMP_DEFLECT_SPEED 0.2f
#define SIMON_GRAVITY			0.0002f

// simon state define
#define MARIO_STATE_IDLE			0
#define MARIO_STATE_WALKING_RIGHT	100
#define MARIO_STATE_WALKING_LEFT	200
#define MARIO_STATE_JUMP			300
#define MARIO_STATE_DIE				400
//simon ani define


#define SIMON_ANI_WALKING_LEFT 0
#define SIMON_ANI_WALKING_RIGHT 1
#define SIMON_ANI_SITDOWN  2



class Simon:public CObjects
{
	int level;
	int untouchable;
	DWORD untouchable_start;

public:
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	virtual void Render();
	void SetState(int state);
	void SetLevel(int l) { level = l; }
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }

	//virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	Simon();
	~Simon();
};


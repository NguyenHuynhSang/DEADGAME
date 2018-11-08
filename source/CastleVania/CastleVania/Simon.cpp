#include "Simon.h"



void Simon::Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects)
{

	// Calculate dx, dy 
	CObjects::Update(dt);

	// Simple fall down
	vy += SIMON_GRAVITY*dt;


}

void Simon::Render()
{
	//int ani;
	//if (state == MARIO_STATE_DIE)
	//	ani = MARIO_ANI_DIE;
	//else
	//	if (level == MARIO_LEVEL_BIG)
	//	{
	//		if (vx == 0)
	//		{
	//			if (nx>0) ani = MARIO_ANI_BIG_IDLE_RIGHT;
	//			else ani = MARIO_ANI_BIG_IDLE_LEFT;
	//		}
	//		else if (vx > 0)
	//			ani = MARIO_ANI_BIG_WALKING_RIGHT;
	//		else ani = MARIO_ANI_BIG_WALKING_LEFT;
	//	}
	//	else if (level == MARIO_LEVEL_SMALL)
	//	{
	//		if (vx == 0)
	//		{
	//			if (nx>0) ani = MARIO_ANI_SMALL_IDLE_RIGHT;
	//			else ani = MARIO_ANI_SMALL_IDLE_LEFT;
	//		}
	//		else if (vx > 0)
	//			ani = MARIO_ANI_SMALL_WALKING_RIGHT;
	//		else ani = MARIO_ANI_SMALL_WALKING_LEFT;
	//	}

}

void Simon::SetState(int state)
{
}

Simon::Simon()
{
}


Simon::~Simon()
{
}

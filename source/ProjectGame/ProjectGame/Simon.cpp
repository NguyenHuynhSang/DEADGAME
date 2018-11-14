#include <algorithm>
#include "debug.h"

#include "Simon.h"
#include "Game.h"
#include "Zombie.h"

void CSIMON::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	// Calculate dx, dy 
	CGameObject::Update(dt);

	// Simple fall down
	vy += SIMON_GRAVITY*dt;

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	// turn off collision when die 
	if (state != SIMON_STATE_DIE)
		CalcPotentialCollisions(coObjects, coEvents);

	// reset untouchable timer if untouchable time has passed
	if (GetTickCount() - untouchable_start > SIMON_UNTOUCHABLE_TIME)
	{
		untouchable_start = 0;
		untouchable = 0;
	}

	// No collision occured, proceed normally
	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		// block 
		x += min_tx*dx + nx*0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
		y += min_ty*dy + ny*0.4f;

		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;

		// Collision logic with Goombas
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (dynamic_cast<CGoomba *>(e->obj))
			{
				CGoomba *goomba = dynamic_cast<CGoomba *>(e->obj);

				// jump on top >> kill Goomba and deflect a bit 
				if (e->ny < 0)
				{
					if (goomba->GetState() != GOOMBA_STATE_DIE)
					{
						goomba->SetState(GOOMBA_STATE_DIE);
						vy = -SIMON_JUMP_DEFLECT_SPEED*2;
					}
				}
				else if (e->nx != 0)
				{
					/*if (untouchable==0)
					{
					if (goomba->GetState()!=GOOMBA_STATE_DIE)
					{
					if (level > SIMON_LEVEL_SMALL)
					{
					level = SIMON_LEVEL_SMALL;
					StartUntouchable();
					}
					else
					SetState(SIMON_STATE_DIE);
					}
					}*/
				}
			}
		}
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}
void CSIMON::Render()
{
	int ani;

	if (state == SIMON_STATE_DIE)
		ani = SIMON_ANI_DIE;
	else
	{

		//check Simon sits
		if (getStateforAniSitandJump == true)
		{
			if (nx > 0)
			{
				ani = SIMON_ANI_SITorJump_RIGHT;
			}
			else
			{
				ani = SIMON_ANI_SITorJump_LEFT;
			}
		}
		else
		{

			if (vx == 0)
			{
				if (nx > 0) 
				{
					if (state==SIMON_STAGE_STAND_FIRE)
					{
						DWORD timeFire = GetTickCount();
						//DebugOut(L" timefire %d",timeFire);
						ani = SIMON_ANI_STAND_FIRE;
					}
					else
					{
						ani = SIMON_ANI_BIG_IDLE_RIGHT;
					
					}
					
				} 
				else ani = SIMON_ANI_BIG_IDLE_LEFT;
			}
			else if (vx > 0)
				ani = SIMON_ANI_BIG_WALKING_RIGHT;
			else ani = SIMON_ANI_BIG_WALKING_LEFT;

		}




	}
	


	int alpha = 255;
	if (untouchable) alpha = 128;
	animations[ani]->Render(x, y, alpha);

	RenderBoundingBox();
}


void CSIMON::SetState(int state)
{
	CGameObject::SetState(state);
	
	switch (state)
	{
	case SIMON_STATE_WALKING_RIGHT:
		vx = SIMON_WALKING_SPEED;
		nx = 1;
		break;
	case SIMON_STATE_WALKING_LEFT:
		vx = -SIMON_WALKING_SPEED;
		nx = -1;
		break;
	case SIMON_STATE_JUMP:
		if (vy==0)
		{
			DebugOut(L"[Line]:%d SIMON state jump",__LINE__);
			vy = -SIMON_JUMP_SPEED_Y;
		}
		break;
	case SIMON_STATE_IDLE:
		vx = 0;
		break;
	case SIMON_STATE_DIE:
		vy = -SIMON_DIE_DEFLECT_SPEED;
		break;
	case SIMON_STAGE_STAND_FIRE:
		
		vx = 0;	// dung khi simon dung vampie killer
		break;
	}
}

//get bounding box dùng để xét va chạm vì khi vẽ sprite lên khung hình thường
//to hơn hình ảnh bên trong,
void CSIMON::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	//x y của SIMON sẽ xét lại
	left = x+14;
	top = y;

	if (level == SIMON_LEVEL_BIG)
	{
		right = x + SIMON_BIG_BBOX_WIDTH-14;
		bottom = y + SIMON_BIG_BBOX_HEIGHT;
	}
	else
	{
	/*	right = x + SIMON_SMALL_BBOX_WIDTH;
		bottom = y + SIMON_SMALL_BBOX_HEIGHT;*/
	}
}


#include "Panther.h"
#include"Textures.h"
#include"HiddenObjects.h"
#include"Camera.h"
#include"Brick.h"
#include"debug.h"


bool checked = false;
bool changeDirection = false;
void CPanther::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);

	//
	// TO-DO: make sure Goomba can interact with the world and to each of them too!
	// 

	if (x - CCamera::GetInstance()->getCamX() <= 500)
	{
		
		if (checked == false)
		{
			state = PANTHER_STATE_RUNNING_LEFT;
			checked = true;
		}
	}
	
	if (state==PANTHER_STATE_DIE)
	{
		isRemove = true;
		return;
	}


	if (state == PANTHER_STATE_RUNNING_LEFT)
	{		
		nx = -1;
		vx = -PANTHER_WALKING_SPEED;
	}
	else if (state==PANTHER_STATE_RUNNING_RIGHT)
	{
		nx = 1;
		vx= PANTHER_WALKING_SPEED;
	}
	else if (state == PANTHER_STATE_JUMPING)
	{
		if (vy == 0)
		{
			vy = -PANTHER_JUMP_SPEED_Y;
			vx = nx > 0 ? PANTHER_JUMP_SPEED_X : -PANTHER_JUMP_SPEED_X;
		}
	}


	for (int i = 0; i < coObjects->size(); i++)
	{
	
		if (dynamic_cast<CHiddenObjects *>(coObjects->at(i)))
		{
			coObjects->erase(coObjects->begin() + i);
		}
	}
	//if (vy != 0)
	//{
	//	state = PANTHER_STATE_JUMPING;
	//}
	vy += PANTHER_GRAVITY*dt;

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEventsResult.clear();
	CalcPotentialCollisions(coObjects, coEvents);
	if (coEvents.size() == 0)
	{
		y += dy;
		x += dx;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			//xu ly va cham voi nen nha
			if (dynamic_cast<CBrick *>(e->obj))
			{
				if (e->ny!=0)
				{
					if ( vy != 0 && state== PANTHER_STATE_JUMPING)
					{
						state = PANTHER_STATE_RUNNING_RIGHT;
						changeDirection = true;
						//DebugOut(L"Co chay vao day \n");
					}
					x += dx;	// nx*0.4f : need to push out a bit to avoid overlapping next frame
					y += min_ty*dy + ny*0.4f;
					if (nx != 0) vx = 0;
					if (ny != 0) vy = 0;
				}
				else if (e->nx!=0)
				{
				
					x += dx;	// nx*0.4f : need to push out a bit to avoid overlapping next frame
					y += min_ty*dy + ny*0.4f;
					if (nx != 0) vx = 0;
					if (ny != 0) vy = 0;
				}
				
			}
			else
			{
				y += dy;
				x += dx;
				if (nx != 0) vx = 0;
				if (ny != 0) vy = 0;
			}
		}
		
		
	}
	// clean up collision events
	for (int i = 0; i < coEvents.size(); i++) delete coEvents[i];
	bool col = false;
	for (int i = 0; i < coObjects->size(); i++)
	{
		LPGAMEOBJECT e = coObjects->at(i);
		if (dynamic_cast<CBrick *>(e))
		{
			CBrick * f = dynamic_cast<CBrick*> (e);

			if (CGameObject::isColliding(this, f) == true)
			{
				col = true;
			}
		}
		if (col==true)
		{
			break;
		}
		
	}

	if (col == false)
	{
		if (state!=PANTHER_STATE_LIEDOWN)
		{
			if (isJumpping==false)
			{
				state = PANTHER_STATE_JUMPING;
				DebugOut(L"Co chay vao day \n");
				isJumpping = true;
			}
		
		}
	}


}

void CPanther::Render()
{
	int ani=0;
	/*if (state==PANTHER_STATE_DIE)
	{
		return;
	}*/
	if (state==PANTHER_STATE_LIEDOWN)
	{
		ani = PANTHER_ANI_LIEDOWN;
	}
	else if (state==PANTHER_STATE_JUMPING)
	{
		ani = PANTHER_ANI_JUMPPING;
	}
	else
	{
		ani = PANTHER_ANI_RUNNING;
	}
	animations[ani]->Render(nx,x,y);
	RenderBoundingBox(x, y);
}

void CPanther::LoadResource()
{
	CSprites * sprites = CSprites::GetInstance();
	CAnimations * animations = CAnimations::GetInstance();
	CTextures * textures = CTextures::GetInstance();
	textures->Add(ID_TEX_PANTHER, L"Resource\\sprites\\Enemies\\PANTHER.png", D3DCOLOR_XRGB(255, 0, 255));
	LPDIRECT3DTEXTURE9 texMisc = textures->Get(ID_TEX_PANTHER);
	sprites->Add(21001, 0, 0, 50, 32, texMisc);
	sprites->Add(21002, 63, 0, 120, 32, texMisc);
	sprites->Add(21003, 127, 0, 188, 32, texMisc);
	sprites->Add(21004, 191, 0, 256, 32, texMisc);
	LPANIMATION ani;

	ani = new CAnimation(100);		// liedown
	ani->Add(21001);
	animations->Add(350, ani);

	ani = new CAnimation(100);		// running
	ani->Add(21002);
	ani->Add(21003);
	animations->Add(351, ani);

	ani = new CAnimation(100);		// Jumping
	ani->Add(21004);
	animations->Add(352, ani);
}

void CPanther::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = x;
	t = y;
	r = x + PANTHER_BBOX_WIDTH;
	b = y + PANTHER_BBOX_HEIGHT;
}

CPanther::CPanther()
{
	AddAnimation(350);
	AddAnimation(351);
	AddAnimation(352);
}


CPanther::~CPanther()
{
}

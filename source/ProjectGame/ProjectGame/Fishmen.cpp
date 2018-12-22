#include "Fishmen.h"
#include"Global.h"
#include"Textures.h"
#include"Camera.h"
#include"debug.h"
void CFishmen::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + FISHMAN_BBOX_WIDTH;
	bottom = y + FISHMAN_BBOX_HEIGHT;
}
float gravity = FISHMAN_GRAVITY;
void CFishmen::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (isEnable==false)
	{
		if (x-CCamera::GetInstance()->getCamX()<600)
		{

			isEnable = true;
		}
		else
		{
			vy = -FISHMAN_JUMP_SPEED_Y;
			return;
		}


	}
	CGameObject::Update(dt);
	//
	// TO-DO: make sure Goomba can interact with the world and to each of them too!
	// 
	DWORD now = GetTickCount();

	if (state==FISHMAN_STATE_FIRE)
	{
		if (now - startFire>FISHMAN_WALKING_TIME)
		{
			state = FISHMAN_STATE_FIRE;
			vx = 0;
			startFire = 0;
		}
	}


	if (startFire!=0)
	{
		if (now - startFire>FISHMAN_WALKING_TIME)
		{
			state = FISHMAN_STATE_FIRE;
			vx = 0;
			startFire = 0;
		}
	}

	

	if (startwalking==false)
	{
		if (vy == 0)
		{
			startFire = GetTickCount();
			state = FISHMAN_STATE_WALKING;
			if (nx>0)
			{
				vx = FISHMAN_WALKING_SPEED;
			}
			else
			{
				vx = -FISHMAN_WALKING_SPEED;
			}
			startwalking = true;
		}
		
	}
	
	vy += FISHMAN_GRAVITY*dt;
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEventsResult.clear();
	coEvents.clear();
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
		
		x += dx;
		if (y<200)
		{
			y += min_ty*dy + ny*0.4f;
			if (ny != 0) vy = 0;
		}
		else
		{
			y += dy;
		}
		
	}
	// clean up collision events
	for (int i = 0; i < coEvents.size(); i++) delete coEvents[i];


}

void CFishmen::Render()
{
	int ani;
	if (state==FISHMAN_STATE_JUMP)
	{
		ani = FISHMAN_ANI_JUMP;
	}
	else if(state == FISHMAN_STATE_WALKING)
	{
		ani = FISHMAN_ANI_WALKING;
	}
	else
	{
		ani = FISHMAN_ANI_FIRE;
	}

	animations[ani]->Render(nx, x, y);

}

void CFishmen::LoadResource()
{
	CSprites * sprites = CSprites::GetInstance();
	CAnimations * animations = CAnimations::GetInstance();
	CTextures * textures = CTextures::GetInstance();
	textures->Add(ID_TEX_FISHMAN, L"Resource\\sprites\\Enemies\\MERMAN.png", D3DCOLOR_XRGB(255, 0, 255));

	///Load texZombie here
	LPDIRECT3DTEXTURE9 texEnemy = textures->Get(ID_TEX_FISHMAN);
	sprites->Add(61001, 0, 0, 32, 64, texEnemy);
	sprites->Add(61002, 32, 0, 64, 64, texEnemy);
	sprites->Add(61003, 64, 0, 94, 64, texEnemy);


	LPANIMATION ani;
	ani = new CAnimation(100);		// fishman JUMP
	ani->Add(61003);
	animations->Add(4001, ani);

	ani = new CAnimation(100);		//  fishman walking
	ani->Add(61003);
	ani->Add(61002);
	animations->Add(4002, ani);


	ani = new CAnimation(100);		//  fishman fire
	ani->Add(61001);
	animations->Add(4003, ani);
}

CFishmen::CFishmen()
{
	AddAnimation(4001);
	AddAnimation(4002);
	AddAnimation(4003);
}


CFishmen::~CFishmen()
{
}

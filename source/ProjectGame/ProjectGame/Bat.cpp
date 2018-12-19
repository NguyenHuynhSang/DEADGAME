#include "Bat.h"
#include"Textures.h"
#include"Global.h"
#include"Camera.h"
#include"debug.h"
void CBat::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + BAT_BBOX_WIDTH;
	bottom = y + BAT_BBOX_HEIGHT;
}


// y tính theo sin x vẫn đúng
// vì x tính theo thời gian nên set y như thế vẫn đúng
void CBat::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (isEnable==false)
	{
		if (x - CCamera::GetInstance()->getCamX() < 500)
		{
			state = BAT_STATE_FLY;
		}
	}

	if (state==BAT_STATE_IDLE)
	{
		return;
	}
	if (state == BAT_STATE_FLY)
	{
		vx = -BAT_FLYING_SPEED_X;
	
	}
	CGameObject::Update(dt);
	

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEventsResult.clear();
	coEvents.clear();
	CalcPotentialCollisions(coObjects, coEvents);

	if (coEvents.size() == 0)
	{
		x += dx;
		y = BAT_OY_HEIGHT * sin(x*0.025) + batOy;
	}
	else
	{
		x += dx;
		y = BAT_OY_HEIGHT * sin(x*0.025) + batOy; //0.025 kéo chu kỳ lớn hơn
	}
	// clean up collision events
	for (int i = 0; i < coEvents.size(); i++) delete coEvents[i];


}

void CBat::Render()
{
	int ani = 0;
	if (state==BAT_STATE_IDLE)
	{
		ani = BAT_ANI_IDLE;	
	}
	if (state == BAT_STATE_FLY)
	{
		ani = BAT_ANI_FLY;
	}
	animations[ani]->Render(nx, x, y);
}

void CBat::LoadResource()
{
	CSprites * sprites = CSprites::GetInstance();
	CAnimations * animations = CAnimations::GetInstance();
	CTextures * textures = CTextures::GetInstance();
	textures->Add(ID_TEX_BAT, L"Resource\\sprites\\Enemies\\BAT.png", D3DCOLOR_XRGB(255, 0, 255));

	///Load texZombie here
	LPDIRECT3DTEXTURE9 texEnemy = textures->Get(ID_TEX_BAT);
	sprites->Add(51001, 0, 0, 30, 32, texEnemy);
	sprites->Add(51002, 30	, 0, 62, 32, texEnemy);
	sprites->Add(51003, 62, 0, 94, 32, texEnemy); 
	sprites->Add(51004, 94, 0, 128, 32, texEnemy); // die sprite


	LPANIMATION ani;
	ani = new CAnimation(100);		// BAT IDLE
	ani->Add(51001);
	animations->Add(2001, ani);

	ani = new CAnimation(100);		//  BAT FLY
	ani->Add(51002);
	ani->Add(51003);
	ani->Add(51004);
	animations->Add(2002, ani);
}

CBat::CBat()
{
	AddAnimation(2001);
	AddAnimation(2002);
}


CBat::~CBat()
{
}

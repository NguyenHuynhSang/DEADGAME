#include "Item.h"
#include"debug.h"
#include"Brick.h"
#include"Ground.h"
#include"Global.h"
#include"HiddenObjects.h"
#include"Textures.h"
#include<time.h>
void CItem::Render()
{

	animations[state]->Render(0, x, y);
//	RenderBoundingBox(x,y);
}
void CItem::createItem()
{
	CGlobal::GetInstance()->objects.push_back(this);
}
void CItem::_rank()
{
	srand(time(NULL));
	int random = rand() % 6 + 1;
	if (random==2)
	{
		random = 3;
	}
	state = random;

}
void CItem::LoadResource()
{
	CSprites * sprites = CSprites::GetInstance();
	CAnimations * animations = CAnimations::GetInstance();
	CTextures * textures = CTextures::GetInstance();
	textures->Add(ID_TEX_ITEM_DANGER, L"Resource\\sprites\\Items\\KNIFE.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_ITEM_BHEART, L"Resource\\sprites\\Items\\BIG_HEART.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_ITEM_NWHIP, L"Resource\\sprites\\Items\\MORNING_STAR.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_ITEM_MHEART, L"Resource\\sprites\\Items\\SMALL_HEART.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_ITEM_WHITE_MONEYBAG, L"Resource\\sprites\\Items\\Money_bag_white.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_ITEM_BLUE_MONEYBAG, L"Resource\\sprites\\Items\\Money_bag_blue.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_ITEM_RED_MONEYBAG, L"Resource\\sprites\\Items\\Money_bag_red.png", D3DCOLOR_XRGB(255, 0, 255));

	LPDIRECT3DTEXTURE9 texBHear = textures->Get(ID_TEX_ITEM_BHEART);
	sprites->Add(70000, 0, 0, 24, 20, texBHear);
	LPDIRECT3DTEXTURE9 texDanger = textures->Get(ID_TEX_ITEM_DANGER);
	sprites->Add(70001, 0, 0, 32, 18, texDanger);
	LPDIRECT3DTEXTURE9 texNWhip = textures->Get(ID_TEX_ITEM_NWHIP);
	sprites->Add(70002, 0, 0, 32, 32, texNWhip);
	LPDIRECT3DTEXTURE9 texMHeart = textures->Get(ID_TEX_ITEM_MHEART);
	sprites->Add(70003, 0, 0, 16, 16, texMHeart);
	LPDIRECT3DTEXTURE9 texWMB = textures->Get(ID_TEX_ITEM_WHITE_MONEYBAG);
	sprites->Add(70004, 0, 0, 30, 30, texWMB);
	LPDIRECT3DTEXTURE9 texBMB = textures->Get(ID_TEX_ITEM_BLUE_MONEYBAG);
	sprites->Add(70005, 0, 0, 30, 30, texBMB);
	LPDIRECT3DTEXTURE9 texRMB = textures->Get(ID_TEX_ITEM_RED_MONEYBAG);
	sprites->Add(70006, 0, 0, 30, 30, texRMB);
	LPANIMATION ani;

	ani = new CAnimation(10000);		// BHEART
	ani->Add(70000);
	animations->Add(901, ani);

	ani = new CAnimation(100);		// danger
	ani->Add(70001);
	animations->Add(902, ani);

	ani = new CAnimation(100);		// NWhip
	ani->Add(70002);
	animations->Add(903, ani);


	ani = new CAnimation(100);		// MHEART
	ani->Add(70003);
	animations->Add(904, ani);


	ani = new CAnimation(100);		// W Money bag
	ani->Add(70004);
	animations->Add(905, ani);


	ani = new CAnimation(100);		// Blue Money bag
	ani->Add(70005);
	animations->Add(906, ani);


	ani = new CAnimation(100);		// red Money bag
	ani->Add(70006);
	animations->Add(907, ani);
}
void CItem::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	if (state==ITEM_STATE_BHEART)
	{
		right = x + BHEART_BBOX_BIG_WIDTH;
		bottom = y + BHEART_BBOX_BIG_HEIGHT;
	}
	if (state == ITEM_STATE_NWHIP)
	{
		right = x + WHIP_UPDATE_BBOX_WIDTH;
		bottom = y + WHIP_UPDATE_BBOX_HEIGHT;
	}
	if (state==ITEM_STATE_DANGER)
	{
		right = x + DAGGER_BBOX_WIDTH;
		bottom = y + DAGGER_BBOX_HEIGHT;
	}
	if (state==ITEM_STATE_MHEART)
	{
		right = x + MHEART_BBOX_WIDTH;
		bottom = y + MHEART_BBOX_HEIGHT;
	}
	if (state == ITEM_STATE_WHITE_MONEYBAG || state == ITEM_STATE_BLUE_MONEYBAG ||state == ITEM_STATE_RED_MONEYBAG)
	{
		right = x + MONEYBAG_BBOX_WIDTH;
		bottom = y + MONEYBAG_BBOX_HEIGHT;
	}
}
void CItem::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	timeShow = GetTickCount();
	if (timeShow-timeStart>ITEM_SHOW_TIME)
	{
		isRemove = true;
		return;
	}
	CGameObject::Update(dt);
	if (state == ITEM_STATE_MHEART)
	{
		vy = ITEM_SPEED_Y*dt;
	}
	else
	{
		vy += ITEM_GRAVITY*dt;
	}

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEventsResult.clear();
	CalcPotentialCollisions(coObjects, coEvents);
	for (int i = 0; i < coEvents.size(); i++)
	{
		if (!dynamic_cast<CBrick *>(coEvents[i]->obj) && !dynamic_cast<CGround *>(coEvents[i]->obj))
		{
			coEvents.erase(coEvents.begin() + i);
		}
	
	}
	if (coEvents.size() == 0)
	{
		if (state==ITEM_STATE_MHEART)
		{
			y += dy;
			x = ITEM_MHEAD_OX_WEIGHT * sin(y*0.15) + mheartox;
		}
		else
		{
			y += dy;
		
		}
		
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
		y += min_ty*dy + ny*0.4f;
		if (ny != 0) vy = 0;
	}
	// clean up collision events
	for (int i = 0; i < coEvents.size(); i++) delete coEvents[i];
	
}





CItem::CItem()
{
	this->AddAnimation(903);
	this->AddAnimation(901);
	this->AddAnimation(902);
	this->AddAnimation(904);
	this->AddAnimation(905);
	this->AddAnimation(906);
	this->AddAnimation(907);
	//carefull
	//item->GetPosition(x, y);
	//thêm vào object mới có thể update, hay bắt sự kiện va chạm
	//vì cái coobject dc lay ra tu object
	//k thêm vào lấy đâu ra mà xét.
	DebugOut(L"\nCreate Items");
	timeStart = GetTickCount();
}


CItem::~CItem()
{
	
}

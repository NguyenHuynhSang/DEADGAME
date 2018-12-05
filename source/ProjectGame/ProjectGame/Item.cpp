#include "Item.h"
#include"debug.h"
#include"Brick.h"
#include"Global.h"
#include"Textures.h"
void CItem::Render()
{

	animations[state]->Render(0, x, y);
	RenderBoundingBox(x,y);
}
void CItem::createItem()
{
	CGlobal::GetInstance()->objects.push_back(this);
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
}
void CItem::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	vy += ITEM_GRAVITY*dt;
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEventsResult.clear();
	CalcPotentialCollisions(coObjects, coEvents);
	if (coEvents.size() == 0)
	{
		y += dy;
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
	CSprites * sprites = CSprites::GetInstance();
	CAnimations * animations = CAnimations::GetInstance();
	CTextures * textures = CTextures::GetInstance();
	LPDIRECT3DTEXTURE9 texBHear = textures->Get(ID_TEX_ITEM_BHEAR);
	sprites->Add(70000, 0, 0, 24, 20, texBHear);
	LPDIRECT3DTEXTURE9 texDanger = textures->Get(ID_TEX_ITEM_DANGER);
	sprites->Add(70001, 0, 0, 24, 20, texDanger);
	PDIRECT3DTEXTURE9 texNWhip = textures->Get(ID_TEX_ITEM_NWHIP);
	sprites->Add(70002, 0, 0, 32, 32, texNWhip);
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

	this->AddAnimation(901);
	this->AddAnimation(902);
	this->AddAnimation(903);
	//carefull
	//item->GetPosition(x, y);
	//thêm vào object mới có thể update, hay bắt sự kiện va chạm
	//vì cái coobject dc lay ra tu object
	//k thêm vào lấy đâu ra mà xét.
	DebugOut(L"\nCreate Items");

}


CItem::~CItem()
{
	
}

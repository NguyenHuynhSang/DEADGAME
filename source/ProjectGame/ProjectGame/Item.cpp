#include "Item.h"
#include"debug.h"
#include"Brick.h"
#include"Global.h"
void CItem::Render()
{

	if (isShow==true)
	{
		animations[state]->Render(0, x, y);
	}
	//RenderBoundingBox();
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
	if (isShow ==false)
	{
		return;
	}

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

}


CItem::~CItem()
{
}

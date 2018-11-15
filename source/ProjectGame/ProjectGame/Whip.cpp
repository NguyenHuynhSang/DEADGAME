#include "Whip.h"	
#include"Torch.h"
#include"Debug.h"
void CWhip::Render()
{
	animations[state]->Render(nx, x, y);
}

void CWhip::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + WHIP_BBOX_WIDTH;
	bottom = y + WHIP_BBOX_HEIGHT;
}

void CWhip::Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects)
{
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEventsResult.clear();
	CalcPotentialCollisions(colliable_objects, coEvents);
	FilterCollisionImmediately(coEvents, coEventsResult);
	for (UINT i = 0; i < coEventsResult.size(); i++)
	{
		LPCOLLISIONEVENT e = coEventsResult[i];
		if (dynamic_cast<CTorch *> (e->obj))
		{
			CTorch *torch = dynamic_cast<CTorch *>(e->obj);
			torch->SetState(TORCH_STATE_DISAPPEAR);
			DebugOut(L"here");
		}
	}
}

CWhip::CWhip()
{
}


CWhip::~CWhip()
{
}

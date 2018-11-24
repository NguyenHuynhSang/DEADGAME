﻿#include "Whip.h"	
#include"Torch.h"
#include"Debug.h"
#include"Item.h"
#include"Global.h"

void CWhip::Render()
{
	if (state == WHIP_STATE_RED)
	{
		if (CAnimations::GetInstance()->Get(WHIP_RED_ANI_ID)->getCurrentFrame() != 11)
		{
			animations[state]->Render(nx, x, y);
			if (nx>0)
			{
				RenderBoundingBox(220 - WHIP_RED_BBOX_WIDTH + x, y + 15);
			}
			else
			{
				RenderBoundingBox(x+25, y + 15);
			}
			
		}
	}
	else
	{
		animations[state]->Render(nx, x, y);
		if (nx>0)
		{
			RenderBoundingBox(190 - WHIP_BBOX_WIDTH + x, y + 15);
		}
		else
		{
			RenderBoundingBox(x + 50,y+15);
		}
		
	}
	
//	RenderBoundingBox();
}

void CWhip::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{


	top = y + 15;	
	bottom = top + WHIP_BBOX_HEIGHT;
	if (nx < 0)
	{
		left = x + 50;
		right = left + WHIP_BBOX_WIDTH;
	}
	else if (nx > 0)
	{
		left = 190 - WHIP_BBOX_WIDTH + x;
		right = left + WHIP_BBOX_WIDTH;
	}
	
	if (state==WHIP_STATE_RED)
	{
		if (nx < 0)
		{
			left = x+25;
			right = left + WHIP_RED_BBOX_WIDTH;
		}
		else if (nx > 0)
		{
			left = 190 - WHIP_RED_BBOX_WIDTH+30 + x;
			right = left + WHIP_RED_BBOX_WIDTH;
		}
	}


}
//phai them cwhip vao object neu k se k update dc coevent
//cách 2 dùng AABB
void CWhip::Update(DWORD dt, vector<LPGAMEOBJECT>* cobjects)
{
	//duyet het cac objects, neu la Ctourch thi
//dung AABB xet 2 cai bounding box co chong len nhau hay khong
// neu co thi co xay ra va cham
	for (int i = 0; i < cobjects->size(); i++)
	{
		
		LPGAMEOBJECT e = cobjects->at(i);
		if (dynamic_cast<CTorch *>(e))
		{
			CTorch * f = dynamic_cast<CTorch*> (e);
			
			if (CGameObject::isColliding(this, f)==true)
			{
					DebugOut(L"Co va cham \n");
					// thuc ra chi ngung render neu va cham chua remove han can toi uu
					f->SetState(TORCH_STATE_DISAPPEAR);
					f->isRemove = true;
			}
		}
	}



}


CWhip::CWhip()
{
}


CWhip::~CWhip()
{
}

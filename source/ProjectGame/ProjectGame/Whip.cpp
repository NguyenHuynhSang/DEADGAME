#include "Whip.h"	
#include"Torch.h"
#include"Debug.h"
void CWhip::Render()
{
	animations[state]->Render(nx, x, y);
	RenderBoundingBox();
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
			
			if (CGameObject::isColliding(f, this)==true)
			{
				//DebugOut(L"Co va cham ");
				// thuc ra chi ngung render neu va cham chua remove han can toi uu
				f->SetState(TORCH_STATE_DISAPPEAR);
				
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

#include "Torch.h"
#include"debug.h"

///get boundingbox xet va cham 
void CTorch::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x +  TORCH_BBOX_WIDTH;
	bottom = y + TORCH_BBOX_HEIGHT;

}



void CTorch::Render()
{
	int ani = TORCH_ANI_BURNING;
	if (state == TORCH_STATE_BURNING) {
		ani = TORCH_ANI_BURNING;
	}
	else
	{
		/*ani = TORCH_ANI_BURNING;*/
	}
	if (state!= TORCH_STATE_DISAPPEAR)
	{
		
		animations[ani]->Render(0, x, y,255);
	}


	RenderBoundingBox(x,y);
	//DebugOut(L"x=%d y=%d \n");
}

void CTorch::SetState(int state)
{
	CGameObject::SetState(state);
}
void CTorch::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) 
{

	if (state==TORCH_STATE_DISAPPEAR)
	{
		item->isShow = true;
	}
	else
	{
		item->isShow = false;
		item->SetPosition(x, y);
	}


}



// vì scene đầu item đc định sẵn k phải rank
void CTorch::setItemState(int nstate)
{
	item->SetState(nstate);
}

//CTorch::CTorch()
//{
//}
//
//
//CTorch::~CTorch()
//{
//}

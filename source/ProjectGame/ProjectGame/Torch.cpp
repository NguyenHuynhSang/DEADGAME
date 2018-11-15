#include "Torch.h"


///get boundingbox xet va cham 
void CTorch::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x +  TORCH_BBOX_WIDTH;
	bottom = y + TORCH_BBOX_HEIGHT;

}

void CTorch::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
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
		animations[ani]->Render(0, x, y);
	}

	//RenderBoundingBox();
}

void CTorch::setNumOfTorchPerScene()
{
}

void CTorch::SetState(int state)
{
	CGameObject::SetState(state);
}

//CTorch::CTorch()
//{
//}
//
//
//CTorch::~CTorch()
//{
//}

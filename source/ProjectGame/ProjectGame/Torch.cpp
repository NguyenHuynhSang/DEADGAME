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
		animations[ani]->Render(0, x, y);
	}
	if (state==TORCH_STATE_DISAPPEAR)
	{
		eff->SetPosition(x, y);
		eff->Render();
		if (CAnimations::GetInstance()->Get(9999)->getCurrentFrame()==3)
		{
			eff->isRemove = true;
		}
	}
		
	//RenderBoundingBox(x,y);
	//DebugOut(L"x=%d y=%d \n");
}

void CTorch::SetState(int state)
{
	CGameObject::SetState(state);
}
void CTorch::LoadResource()
{
	CSprites * sprites = CSprites::GetInstance();
	CAnimations * animations = CAnimations::GetInstance();
	CTextures * textures = CTextures::GetInstance();
	textures->Add(ID_TEX_TORCH, L"Resource\\sprites\\Ground\\0.png", D3DCOLOR_XRGB(255, 0, 255));
	//torch
	LPDIRECT3DTEXTURE9 texTch = textures->Get(ID_TEX_TORCH);
	sprites->Add(40000, 0, 0, 32, 64, texTch);
	sprites->Add(40001, 32, 0, 64, 64, texTch);
	LPANIMATION ani;


	ani = new CAnimation(200);  //torch
	ani->Add(40000);
	ani->Add(40001);
	animations->Add(801, ani);





}
void CTorch::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) 
{
	if (state==TORCH_STATE_DISAPPEAR)
	{
		if (eff->isRemove==true)
		{
			item = new CItem();
			item->SetPosition(x, y);
			item->SetState(ItemState);
			item->createItem();
			item->mheartox = x;
			isRemove = true;
		}
		
	}

}



// vì scene đầu item đc định sẵn k phải rank
void CTorch::setItemState(int nstate)
{
	ItemState = nstate;
	
}

//CTorch::CTorch()
//{
//}
//
//
//CTorch::~CTorch()
//{
//}

#include "Torch.h"
#include"debug.h"

///get boundingbox xet va cham 
void CTorch::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;

	right = x +  TORCH_BBOX_WIDTH;
	bottom = y + TORCH_BBOX_HEIGHT;
	if (state == TORCH_STATE_SMAIL)
	{
		right = x + CANDLE_BBOX_WIDTH;
		bottom = y + CANDLE_BBOX_HEIGHT;
	}
}



void CTorch::Render()
{
	int ani = TORCH_ANI_BIG;
	if (state == TORCH_STATE_BIG) 
	{
		ani = TORCH_ANI_BIG;
		animations[ani]->Render(0, x, y);
		return;
	}
	else if (state == TORCH_STATE_SMAIL)
	{
		ani = TORCH_ANI_SMAIL;
		animations[ani]->Render(0, x, y);
		return;

	} else if (state==TORCH_STATE_DISAPPEAR)
	{
		eff->SetPosition(x, y);
		eff->Render();
		if (CAnimations::GetInstance()->Get(9999)->getCurrentFrame()==3)
		{
			eff->isRemove = true;
		}
	}
	
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
	textures->Add(31, L"Resource\\sprites\\Ground\\1.png", D3DCOLOR_XRGB(255, 0, 255));
	//torch
	LPDIRECT3DTEXTURE9 texTch = textures->Get(ID_TEX_TORCH);
	sprites->Add(40000, 0, 0, 32, 64, texTch);
	sprites->Add(40001, 32, 0, 64, 64, texTch);


	LPDIRECT3DTEXTURE9 texcandle = textures->Get(31);
	sprites->Add(40002, 0, 0, 16, 32, texcandle);
	sprites->Add(40003, 16, 0, 32, 32, texcandle);
	LPANIMATION ani;


	ani = new CAnimation(200);  //torch
	ani->Add(40000);
	ani->Add(40001);
	animations->Add(801, ani);

	ani = new CAnimation(50);  //torch
	ani->Add(40002);
	ani->Add(40003);
	animations->Add(802, ani);




}
void CTorch::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) 
{
	if (state==TORCH_STATE_SMAIL)
	{
		candle = true;
	}
	if (state==TORCH_STATE_DISAPPEAR)
	{
		if (eff->isRemove==true)
		{
			item = new CItem();
			item->SetPosition(x, y);
			
			item->SetState(ItemState);
			if (candle == true)
			{
				item->_rank();
			}
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

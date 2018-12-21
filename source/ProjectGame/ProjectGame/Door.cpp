#include "Door.h"
#include"Textures.h"
#include"Global.h"

void CDoor::Render()
{
	int ani;
	if (state==DOOR_STATE_BIGDOOR)
	{
		ani = DOOR_ANI_BIGDOOR;
	}
	else
	{
		ani = DOOR_ANI_SMAILDOOR;
	}
	animations[ani]->Render(0,x,y);
}

void CDoor::LoadResource()
{
	CSprites * sprites = CSprites::GetInstance();
	CAnimations * animations = CAnimations::GetInstance();
	CTextures * textures = CTextures::GetInstance();
	textures->Add(ID_TEX_DOOR_LV2, L"Resource\\sprites\\Ground\\10.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_DOOR_LV1, L"Resource\\sprites\\bdoor.png", D3DCOLOR_XRGB(255, 0, 255));
	//textures->Add(ID_TEX_DOOR_LV2, L"Resource\\sprites\\Ground\\2.png", D3DCOLOR_XRGB(225, 0, 248));
	LPDIRECT3DTEXTURE9 texMisc = textures->Get(ID_TEX_DOOR_LV2);
	PDIRECT3DTEXTURE9 texdoorlv1 = textures->Get(ID_TEX_DOOR_LV1);
	sprites->Add(31116, 0, 0, 16, 96, texMisc);
	sprites->Add(31117, 0, 0, 190, 288, texdoorlv1);
	LPANIMATION ani;

	ani = new CAnimation(100);		// door lv2
	ani->Add(31117);
	animations->Add(627, ani);


	ani = new CAnimation(100);		// door lv2
	ani->Add(31116);
	animations->Add(626, ani);
}

void CDoor::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = x;
	t = y;
	r = x + DOOR_BBOX_WIDTH;
	b = y + DOOR_BBOX_HEIGHT;
}

CDoor::CDoor()
{
	AddAnimation(626);
	AddAnimation(627);
}


CDoor::~CDoor()
{
}

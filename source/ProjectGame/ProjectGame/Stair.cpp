#include "Stair.h"
#include"Textures.h"


void CStair::Render()
{
	animations[state]->Render(nx, x, y);
	//RenderBoundingBox(x, y);
}

void CStair::LoadResource()
{

	CSprites * sprites = CSprites::GetInstance();
	CAnimations * animations = CAnimations::GetInstance();
	CTextures * textures = CTextures::GetInstance();
	textures->Add(ID_TEX_STAIR, L"Resource\\sprites\\Ground\\3_.png", D3DCOLOR_XRGB(255, 0, 255));
	LPDIRECT3DTEXTURE9 texMisc = textures->Get(ID_TEX_STAIR);
	sprites->Add(20005, 0, 0, 32, 32, texMisc);
	LPANIMATION ani;

	ani = new CAnimation(100);		// brick
	ani->Add(20005);
	animations->Add(605, ani);

}

void CStair::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = x;
	t = y;
	r = x + STAIR_BBOX_WIDTH;
	b = y + STAIR_BBOX_HEIGHT;

}

CStair::CStair()
{
	AddAnimation(605);
}


CStair::~CStair()
{
}

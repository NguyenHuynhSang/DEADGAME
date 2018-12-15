#include "Effect.h"
#include"Textures.h"
#include"Global.h"

void CEffect::LoadResource()
{
	CSprites * sprites = CSprites::GetInstance();
	CAnimations * animations = CAnimations::GetInstance();
	CTextures * textures = CTextures::GetInstance();

	textures->Add(ID_TEX_EFFECT, L"Resource\\sprites\\Effect.png", D3DCOLOR_XRGB(255, 0, 255));
	LPDIRECT3DTEXTURE9 texEffect = textures->Get(ID_TEX_EFFECT);
	sprites->Add(101, 0, 0, 32, 64, texEffect);
	sprites->Add(102, 32, 0, 64, 64, texEffect);
	sprites->Add(103, 64, 0, 96, 64, texEffect);
	sprites->Add(104, 0, 0, 0, 0, texEffect);
	LPANIMATION ani;

	ani = new CAnimation(150);		// brick
	ani->Add(101);
	ani->Add(102);
	ani->Add(103);
	ani->Add(104);
	animations->Add(9999, ani);

}
void CEffect::Render()
{
	if (isRemove == false)
	{
		animations[state]->Render(0, x, y);
	}
}

void CEffect::GetBoundingBox(float & l, float & t, float & r, float & b)
{
		
}

CEffect::CEffect():CGameObject()
{
	AddAnimation(9999);

}


CEffect::~CEffect()
{
}

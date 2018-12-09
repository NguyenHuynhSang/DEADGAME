#include "Effect.h"
#include"Textures.h"


void CEffect::LoadResource()
{
	CSprites * sprites = CSprites::GetInstance();
	CAnimations * animations = CAnimations::GetInstance();
	CTextures * textures = CTextures::GetInstance();

}

void CEffect::Render()
{
	animations[state]->Render(0, x, y);
}

void CEffect::GetBoundingBox(float & l, float & t, float & r, float & b)
{
		
}

CEffect::CEffect():CGameObject()
{
	//ex exploision

}


CEffect::~CEffect()
{
}

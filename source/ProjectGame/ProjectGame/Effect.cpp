#include "Effect.h"



void CEffect::LoadResource()
{
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

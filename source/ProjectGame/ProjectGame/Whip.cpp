#include "Whip.h"



void CWhip::Render()
{
	animations[state]->Render(nx, x, y);
}

void CWhip::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + WHIP_BBOX_WIDTH;

	bottom = y + WHIP_BBOX_HEIGHT;
}

void CWhip::Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects)
{
}

CWhip::CWhip()
{
}


CWhip::~CWhip()
{
}

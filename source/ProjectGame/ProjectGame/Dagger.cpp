#include "Dagger.h"



void CDagger::Render()
{
}

void CDagger::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = left + DAGGER_BBOX_WIDTH;
	bottom = top + DAGGER_BBOX_HEIGHT;
}

void CDagger::Update(DWORD dt, vector<LPGAMEOBJECT>* co)
{
}

CDagger::CDagger()
{
}


CDagger::~CDagger()
{
}

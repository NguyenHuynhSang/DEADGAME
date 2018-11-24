#include "Dagger.h"
#include"Camera.h"
#include"Global.h"

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
	float camx, camy;
	CCamera::GetInstance()->getCamera(camx, camy);
	//remove danger khi ra khỏi ViewPort
	if (x<(int)camx || x>(int)camx+SCREEN_WIDTH)
	{
		this->isRemove = true;
	}

}

CDagger::CDagger()
{
}


CDagger::~CDagger()
{
}

#include "Objects.h"


void CObjects::AddAnimation(int aniId)
{
//	LPANIMATION ani = CAnimations::GetInstance()->Get(aniId);
	//animations.push_back(ani);
}

void CObjects::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	this->dt = dt;
	dx = vx*dt;
	dy = vy*dt;
}

CObjects::CObjects()
{
	x = y = 0;
	vx = vy = 0;
	nx = 1;

}


CObjects::~CObjects()
{
}

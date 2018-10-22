#include "Objects.h"



void CObjects::Update(DWORD dt)
{
	x += vx*dt;
	if ((vx>0 && x > 290) || (x < 0 && vx<0)) vx = -vx;
}

CObjects::CObjects()
{
	x = y = 0;
	vx = 0.07f;

}


CObjects::~CObjects()
{
}

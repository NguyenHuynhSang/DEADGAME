#include "HiddenObjects.h"



void CHiddenObjects::Render()
{
	RenderBoundingBox(x, y);
}

void CHiddenObjects::LoadResource()
{
}

void CHiddenObjects::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = x;
	t = y;
	r = x + _width;
	b = y + _height;
}

CHiddenObjects::CHiddenObjects()
{
	_width = 32;
	_height = 32;
}


CHiddenObjects::~CHiddenObjects()
{
}

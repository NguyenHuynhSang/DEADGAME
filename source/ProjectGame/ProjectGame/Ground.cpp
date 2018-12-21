#include "Ground.h"



void CGround::Render()
{
	RenderBoundingBox(x,y);
}

void CGround::LoadResource()
{
}



void CGround::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = x;
	t = y;
	r = x + _width;
	b = y + _height;
}

CGround::CGround()
{
	_width = 32;
	_height = 32;
}


CGround::~CGround()
{
}

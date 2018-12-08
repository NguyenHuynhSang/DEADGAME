#include "Brick.h"
#include"Camera.h"
#include"Global.h"
void CBrick::Render()
{
	float camX,camY;
	CCamera::GetInstance()->getCamera(camX,camY);
	if (x<0||x>camX+SCREEN_WIDTH)
	{

	}
	else
	{
		animations[0]->Render(0, x, y);
		//RenderBoundingBox();
	}
	}

void CBrick::LoadResource()
{
}


void CBrick::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = x + BRICK_BBOX_WIDTH;
	b = y + BRICK_BBOX_HEIGHT;
}
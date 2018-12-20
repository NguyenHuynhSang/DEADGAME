#include "Brick.h"
#include"Camera.h"
#include"Global.h"
#include"Textures.h"
void CBrick::Render()
{

		animations[state]->Render(0, x, y);
		//RenderBoundingBox(x,y);
}

void CBrick::LoadResource()
{
	CSprites * sprites = CSprites::GetInstance();
	CAnimations * animations = CAnimations::GetInstance();
	CTextures * textures = CTextures::GetInstance();
	textures->Add(ID_TEX_BRICK, L"Resource\\sprites\\Ground\\2.png", D3DCOLOR_XRGB(225, 0, 248));
	LPDIRECT3DTEXTURE9 texMisc = textures->Get(ID_TEX_BRICK);
	sprites->Add(20001, 0, 0, 32, 32, texMisc);
	sprites->Add(20002, 50, 0, 82, 32, texMisc);
	LPANIMATION ani;

	ani = new CAnimation(100);		// brick
	ani->Add(20001);
	animations->Add(601, ani);

	ani = new CAnimation(100);		// brick
	ani->Add(20002);
	animations->Add(602, ani);

}


void CBrick::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = x + BRICK_BBOX_WIDTH;
	b = y + BRICK_BBOX_HEIGHT;
}

CBrick::CBrick()
{
	AddAnimation(601);
	AddAnimation(602);
}

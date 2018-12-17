#include "BlackBoard.h"
#include"Textures.h"

CBlackBoard * CBlackBoard::__instance = NULL;

CBlackBoard *CBlackBoard::GetInstance()
{
	if (__instance == NULL) __instance = new CBlackBoard();
	return __instance;
}
void CBlackBoard::Render()
{
	animations[0]->Render(0, x, y);
}

void CBlackBoard::LoadResource()
{
	CSprites * sprites = CSprites::GetInstance();
	CAnimations * animations = CAnimations::GetInstance();
	CTextures * textures = CTextures::GetInstance();
	textures->Add(ID_TEX_BLACKBOARD, L"Resource\\sprites\\blackboard.png", D3DCOLOR_XRGB(225, 0, 255));
	LPDIRECT3DTEXTURE9 texMisc = textures->Get(ID_TEX_BLACKBOARD);
	
	sprites->Add(12345, 0, 0, 520, 80, texMisc);
	LPANIMATION ani;

	ani = new CAnimation(100);		// brick
	ani->Add(12345);
	animations->Add(257, ani);
}

void CBlackBoard::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = x;
	t = y;
	r = x + 640;
	b = y + 50;
}

CBlackBoard::CBlackBoard()
{
	LoadResource();
	AddAnimation(257);
}


CBlackBoard::~CBlackBoard()
{
}

#include "GameUI.h"
#include"Game.h"
#include"Sprites.h"
#include"Textures.h"
#include"Global.h"
#include"Camera.h"
CGameUI * CGameUI::__instance = NULL;

CGameUI *CGameUI::GetInstance()
{
	if (__instance == NULL) __instance = new CGameUI();
	return __instance;
}

void CGameUI::Update(int sHP, int bHP, int time, int state, int cweapon)
{
}

void CGameUI::Render()
{
	CSprites * sprites = CSprites::GetInstance();
	RECT r;
	SetRect(&r, 0, 10, 640, 80);
	
	sprites->GetInstance()->Get(12345)->Draw(0,327,30,255,true);
	CGame::GetInstance()->DrawTextUI(_UIinfor, r);
}

void CGameUI::LoadResource()
{
	CSprites * sprites = CSprites::GetInstance();
	CAnimations * animations = CAnimations::GetInstance();
	CTextures * textures = CTextures::GetInstance();
	textures->Add(ID_TEX_BLACKBOARD, L"Resource\\sprites\\blackboard.png", D3DCOLOR_XRGB(225, 0, 255));
	LPDIRECT3DTEXTURE9 texMisc = textures->Get(ID_TEX_BLACKBOARD);

	sprites->Add(12345, 0, 0, 96, 50, texMisc);
}

CGameUI::CGameUI()
{
	_UIinfor = " SCORE-000000                         TIME 0000                       STAGE 00  \n PLAYER                                                                      00 \n ENERMY                                                                     00  ";
	
}


CGameUI::~CGameUI()
{
}

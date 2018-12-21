#include "GameUI.h"
#include"Game.h"
#include"Sprites.h"
#include"Textures.h"
#include"Global.h"
#include"SceneManager.h"
#include"Camera.h"
#include"Simon.h"
CGameUI * CGameUI::__instance = NULL;

CGameUI *CGameUI::GetInstance()
{
	if (__instance == NULL) __instance = new CGameUI();
	return __instance;
}

void CGameUI::Update()
{
	string state = std::to_string(CSceneManager::GetInstance()->getState());
	string heart= std::to_string(CSIMON::GetInstance()->getHeart());
	_UIinfor = " SCORE-000000                         ";
	_UIinfor += "TIME 0000                       ";
	_UIinfor += "STAGE 0"+state;
	_UIinfor += "\n PLAYER                                                                      "+heart;
	_UIinfor += "\n ENERMY                                                                     01";
}

void CGameUI::Render()
{
	CSprites * sprites = CSprites::GetInstance();
	RECT r;
	SetRect(&r, 0, 10, 640, 80);
	
	sprites->GetInstance()->Get(12345)->Draw(0,327,30,255,true);
	CGame::GetInstance()->DrawTextUI(_UIinfor, r);
	if (CSIMON::GetInstance()->getcurrentSubWeapon() == 1)
	{
		sprites->GetInstance()->Get(70001)->Draw(0, 327+10, 30+10, 255, true);
	}
	
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
	_UIinfor = " SCORE-000000                         ";
	_UIinfor += "TIME 0000                            ";
	_UIinfor += "STAGE 00  ";
	_UIinfor += "\n PLAYER                                                                      05";
	_UIinfor += "\n ENERMY                                                                     01";
	
}


CGameUI::~CGameUI()
{
}

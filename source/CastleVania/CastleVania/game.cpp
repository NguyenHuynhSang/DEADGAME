#include "Game.h"
#include"Objects.h"
CGame * CGame::__instance = NULL;

void CGame::Init(HWND hWnd)
{

	HRESULT rs;
	graphic = new graphics();

	graphic->InitDirect(hWnd, 800, 600, true);
	graphic->initsprite();
//	graphic->InitSprite();
	//graphic->Draw(1, 1, NULL, 20, 20, 20, 20, 255);
	//LoadResource();
}

void CGame::Draw()
{
	//graphic->InitSprite();
}

void CGame::render()
{
	graphic->render_frame();
}

void CGame::LoadResource()
{
	CTextures * textures = CTextures::GetInstance();

	textures->Add(0, L"mario.png", D3DCOLOR_XRGB(176, 224, 248));
	CSprites * sprites = CSprites::GetInstance();
	LPDIRECT3DTEXTURE9 texMario = textures->Get(0);

	// readline => id, left, top, right 
	sprites->Add(10001, 246, 154, 259, 181, texMario);
	sprites->Add(10002, 275, 154, 290, 181, texMario);
	sprites->Add(10003, 304, 154, 321, 181, texMario);

	sprites->Add(10011, 186, 154, 199, 181, texMario);
	sprites->Add(10012, 155, 154, 170, 181, texMario);
	sprites->Add(10013, 125, 154, 140, 181, texMario);

	//mario = new CObjects();
	//graphic->InitSprite(textures->Get(0));
	//graphic->Draw(10, 10, textures->Get(0), 10, 10, 10, 10, 255);

}

CGame * CGame::GetInstance()
{
	if (__instance == NULL) __instance = new CGame();
	return __instance;
}

void CGame::backbuffer()
{
	graphic->ShowBackBuffer();
}

CGame::CGame()
{

	//graphic->InitDirect(hWnd, 800, 600, 1);
}


CGame::~CGame()
{
}

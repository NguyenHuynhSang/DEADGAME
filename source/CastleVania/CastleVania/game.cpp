#include "Game.h"
#include"Objects.h"
#include"Global.h"
CGame * CGame::__instance = NULL;

void CGame::Init(HWND hWnd)
{

//	HRESULT rs;
	graphic = graphics::GetInstance();

	graphic->InitDirect(hWnd, 800, 600, true);
	//graphic->initsprite();
	
	LoadResource();
	//graphic->drawSprite(1, 1, NULL, 0, 0, 20, 20);
}

void CGame::Draw()
{

}
float i = 1;

void CGame::render()
{
	Global *t = Global::GetInstance();
	//t = abc::GetInstance();
	CSprites * sprites = CSprites::GetInstance();
	CTextures * textures = CTextures::GetInstance();

	sprites->Add(20000, 20, 20, 3000, 400, textures->Get(1));
	graphic->Clear();
	graphic->Begin();
	sprites->Get(20000)->Draw(0,0);
	
	if (t->Get() ==1)
	{
		i += 5;
	}
	sprites->Get(10001)->Draw(20+i, 20);
	graphic->End();
	
	graphic->Present();

}

///here load all resource
void CGame::LoadResource()
{
	CTextures * textures = CTextures::GetInstance();

	textures->Add(0, L"Resource\\sprites\\Simon.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(1, L"Resource\\sprites\\lv2.png",NULL);
	//textures->Add(1, L"mario.png", D3DCOLOR_XRGB0255, 255, 255));
	CSprites * sprites = CSprites::GetInstance();
	LPDIRECT3DTEXTURE9 texMario = textures->Get(0);
	sprites->Add(20000, 0, 80, 3000, 400, textures->Get(1));
	// readline => id, left, top, right 
	sprites->Add(10001, 1, 1, 60, 70, texMario);
	sprites->Add(10002, 1, 1, 30, 30, texMario);
	sprites->Add(10003, 304, 154, 321, 181, texMario);

	sprites->Add(10011, 186, 154, 199, 181, texMario);
	sprites->Add(10012, 155, 154, 170, 181, texMario);
	sprites->Add(10013, 125, 154, 140, 181, texMario);
	
	sprites->Get(10001)->Draw(70, 0, 255);
	//mario = new CObjects();
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

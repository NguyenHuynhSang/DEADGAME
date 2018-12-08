﻿/* =============================================================
INTRODUCTION TO GAME PROGRAMMING SE102

SAMPLE 04 - COLLISION

This sample illustrates how to:

1/ Implement SweptAABB algorithm between moving objects
2/ Implement a simple (yet effective) collision frame work

Key functions:
CGame::SweptAABB
CGameObject::SweptAABBEx
CGameObject::CalcPotentialCollisions
CGameObject::FilterCollision

CGameObject::GetBoundingBox

================================================================ */

#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>

#include "debug.h"
#include "Game.h"
#include "GameObject.h"
#include "Textures.h"
#include "Global.h"
#include "Simon.h"
#include "Brick.h"
#include "ghoul.h"
#include "Torch.h"
#include "TileMap.h"
#include "Effect.h"
#include"Camera.h"
#include"Cell.h"
#include"SceneManager.h"
#define WINDOW_CLASS_NAME L"CastleVania"
#define MAIN_WINDOW_TITLE L"CastleVania"
///Clear background to black
#define BACKGROUND_COLOR D3DCOLOR_XRGB(0, 0, 0)

// kích thước mặc định của Window


#define MAX_FRAME_RATE 120

#define ID_TEX_SIMON 0
#define ID_TEX_ENEMY 10
#define ID_TEX_MISC 20
#define ID_TEX_TORCH 30
#define ID_BACKGROUND 1000

CGame *game;
CSIMON *SIMON;
CGhoul *goomba;
CTileMap *tileG;
Cells * cell;
CSceneManager *scene;
class CSampleKeyHander : public CKeyEventHandler
{
	virtual void KeyState(BYTE *states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
};

CSampleKeyHander * keyHandler;

void CSampleKeyHander::OnKeyDown(int KeyCode)
{
	//DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	switch (KeyCode)
	{
	case DIK_C:
		if (SIMON->GetState() == SIMON_STATE_UPWHIP)
		{
			DebugOut(L"State Upwhip \n");
			return;
		}
		SIMON->isUsesW = true;
		SIMON->isDelay = true;
		SIMON->SetState(SIMON_STATE_STAND_FIGHTING);
		break;


	case DIK_F:
		//DebugOut(L"Press Fighting  \n");
		if (SIMON->GetState()==SIMON_STATE_UPWHIP)
		{
			return;
		}
		SIMON->SetState(SIMON_STATE_STAND_FIGHTING);
		break;
	case DIK_SPACE:
		if (SIMON->GetState() == SIMON_STATE_JUMP || SIMON->GetState()== SIMON_STATE_STAND_FIGHTING || SIMON->GetState() == SIMON_STATE_UPWHIP)
		{
			return;
		}
			SIMON->SetState(SIMON_STATE_JUMP);
		
		break;
	case DIK_A: // reset
		SIMON->SetState(SIMON_STATE_IDLE);
		SIMON->SetPosition(100.0f, 200.0f);
		///fix cam when reset
		game->setCam(SCREEN_WIDTH / 2,NULL);
		SIMON->SetSpeed(0, 0);
		break;
	}

		
}

void CSampleKeyHander::OnKeyUp(int KeyCode)
{
	DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);
}

///bắt sự kiện bàn phím và cập nhật trạng thái
void CSampleKeyHander::KeyState(BYTE *states)
{
	// Nên dùng time để xử lý vì dùng frame cuối vừa đến frame cuối ani sẽ dừng
	//mất delay time cần có phương pháp hiệu quả hon
	/// xong

	SIMON->isJump=false;
	if (SIMON->isUpWhip == true)
	{
		SIMON->SetState(SIMON_STATE_UPWHIP);
		DebugOut(L"UpWHIP\n");
		return;
	}
	// disable control key when SIMON die 
	if (SIMON->GetState() == SIMON_STATE_DIE) return;


	if (SIMON->GetState() == SIMON_STATE_STAND_FIGHTING)
	{
		if (SIMON->isSitting==true)
		{
			if (CAnimations::GetInstance()->Get(506)->getCurrentFrame() != 3)
			{
				return;
			}
			else
			{
				SIMON->isDelay = false;
				CAnimations::GetInstance()->Get(506)->setCurrentFrame(-1);
			}
		}
		else
		{
			if (CAnimations::GetInstance()->Get(502)->getCurrentFrame() != 3)
			{
				DebugOut(L"State fighting but  working \n");
				return;
			}
			else
			{
				SIMON->isDelay = false;
				// sửa lỗi bị delay
				CAnimations::GetInstance()->Get(502)->setCurrentFrame(-1);
			}
		}

		
	}
	if (SIMON->GetState()==SIMON_STATE_JUMP && SIMON->isTouchGr()==false)
	{
	
			SIMON->isJump = true;
			return;
	}




	if (game->IsKeyDown(DIK_DOWN))
	{
		SIMON->isJump = true;
		// set state tranh truong hop nguoi dung bam cung luc ngoi va toi
		SIMON->SetState(SIMON_STATE_IDLE);
		SIMON->isSitting = true;
		return;
	}
	else { SIMON->isSitting = false; }



	if (game->IsKeyDown(DIK_RIGHT))         //arrow right
	{
		SIMON->SetState(SIMON_STATE_WALKING_RIGHT);
	}
	else if (game->IsKeyDown(DIK_LEFT))       //arrow left
	{
		SIMON->SetState(SIMON_STATE_WALKING_LEFT);
	}

	else {
		SIMON->SetState(SIMON_STATE_IDLE);
	}
	

}

LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

/*
Load all game resources
In this example: load textures, sprites, animations and SIMON object

TO-DO: Improve this function by loading texture,sprite,animation,object from file
*/

/*====================================================================
// LOGIC CỦA ANIMATION
// Ví dụ SIMON
// ANIMATION(đi,chạy,nhảy....) sẽ được thêm vào ngăn xếp
// Các animation của simon đã được định nghĩa sẵn trong class là
// số tt của ani đã được thêm vào ngăn xếp
// Lúc này muốn animation hoạt động đúng xem phương thức Render của
// class simon
//===================================================================*/

void LoadResources()
{
	CTextures * textures = CTextures::GetInstance();

	textures->Add(ID_TEX_SIMON, L"Resource\\sprites\\Simon\\Simon_ver_editted.png", D3DCOLOR_XRGB(255,0, 255));
	textures->Add(ID_TEX_MISC, L"Resource\\sprites\\Ground\\2.png", D3DCOLOR_XRGB(225, 0, 248));
	textures->Add(ID_TEX_ENEMY, L"Resource\\sprites\\Enemies\\ZOMBIE.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_TORCH, L"Resource\\sprites\\Ground\\0.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_BACKGROUND, L"Resource\\sprites\\lv1.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_BBOX, L"Resource\\sprites\\bbox.png", D3DCOLOR_XRGB(201, 191, 231));
	//item tex load
	textures->Add(ID_TEX_ITEM_BHEAR, L"Resource\\sprites\\Items\\BIG_HEART.png", D3DCOLOR_XRGB(255, 0, 255));

	textures->Add(ID_TEX_ITEM_NWHIP, L"Resource\\sprites\\Items\\MORNING_STAR.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(-10, L"data\\map\\tileset.BMP", D3DCOLOR_XRGB(255, 255, 255));
	textures->Add(ID_TEX_WHIP, L"Resource\\sprites\\Weapons\\Whip.png", D3DCOLOR_XRGB(255, 0, 255));
	CSprites * sprites = CSprites::GetInstance();
	CAnimations * animations = CAnimations::GetInstance();


	LPDIRECT3DTEXTURE9 texMap = textures->Get(-10); //tex Map
	tileG = new CTileMap();
	tileG->SetMSize(1536, 384);
	tileG->SetTileSetHeight(640, 128);
	tileG->LoadTile("data\\map\\tileset.txt", texMap);
	




	LPDIRECT3DTEXTURE9 texSimon = textures->Get(ID_TEX_SIMON);
	// big
	sprites->Add(10001, 28+27-30, 3, 28+27+30,64, texSimon);		// idle right
	sprites->Add(10002, 92-30 + 27, 3, 92+30 + 27, 64, texSimon);		// walk
	sprites->Add(10003, 150-30 + 27, 3, 150 + 30 + 27, 64, texSimon);
	sprites->Add(10004, 210-30 + 27, 3, 210+30 + 27, 64, texSimon);

	sprites->Add(10016, 268-31 + 27, 3, 268+31 + 27, 64, texSimon);//Simon sit Right


	sprites->Add(10017, 356-30, 3, 356 +30, 64, texSimon);//Simon stand fight
	sprites->Add(10018, 427-30, 3, 427+30, 64, texSimon);
	sprites->Add(10019, 501-30, 3, 501+30, 64, texSimon);



	sprites->Add(10021, 450-30+27, 67, 450+30 + 27, 130, texSimon);//Simon sit fight
	sprites->Add(10022, 28-30 + 27, 134, 28+30 + 27, 196, texSimon);
	sprites->Add(10023, 88-30 + 27, 134, 88+30 + 27, 196, texSimon);



	sprites->Add(10051, 58-30, 198, 58+30, 264, texSimon);//Simon Up whip
	sprites->Add(10052, 90 - 30 + 27, 198, 90 + 30 + 27, 264, texSimon);
	sprites->Add(10053, 150 - 30 + 27, 198, 150 + 30 + 27, 264, texSimon);
	sprites->Add(10054, 210-30 + 27, 198, 210+30 + 27, 264, texSimon);


	sprites->Add(10099, 215, 120, 231, 135, texSimon);		// die 

	//torch
	LPDIRECT3DTEXTURE9 texTch = textures->Get(ID_TEX_TORCH);
	sprites->Add(40000,0,0,32,64, texTch);
	sprites->Add(40001, 32, 0, 64, 64, texTch);



	LPDIRECT3DTEXTURE9 texMisc = textures->Get(ID_TEX_MISC);
	sprites->Add(20001, 0, 0, 30, 30, texMisc);

	///Load texZombie here
	LPDIRECT3DTEXTURE9 texEnemy = textures->Get(ID_TEX_ENEMY);
	sprites->Add(30001, 0, 0, 34, 63, texEnemy);
	sprites->Add(30002, 31, 0, 65, 63, texEnemy);

	sprites->Add(30003, 45, 21, 61, 29, texEnemy); // die sprite



	LPANIMATION ani;


	


	ani = new CAnimation(150);	// idle big right
	ani->Add(10001);
	animations->Add(400, ani);

	ani = new CAnimation(150);	// walk right big
	ani->Add(10001);
	ani->Add(10002);
	ani->Add(10003);
	ani->Add(10004);
	animations->Add(500, ani);

	ani = new CAnimation(100); //simon sit 
	ani->Add(10016);
	animations->Add(505, ani);


	ani = new CAnimation(WHIP_DELAY_TIME);//simon stand fight
	ani->Add(10017);
	ani->Add(10018);
	ani->Add(10019);
	ani->Add(10001);
	animations->Add(502, ani);



	ani = new CAnimation(WHIP_DELAY_TIME); //simon sit  fight
	ani->Add(10021);
	ani->Add(10022);
	ani->Add(10023);
	ani->Add(10016);
	animations->Add(506, ani);



	ani = new CAnimation(100); //simon up whip
	ani->Add(10051);
	ani->Add(10052);
	ani->Add(10053);
	ani->Add(10054);	
	ani->Add(10001);
	animations->Add(507, ani);


	ani = new CAnimation(100);		// SIMON die
	ani->Add(10099);
	animations->Add(599, ani);
	







	ani = new CAnimation(200);  //torch
	ani->Add(40000);
	ani->Add(40001);
	animations->Add(801, ani);



	ani = new CAnimation(100);		// brick
	ani->Add(20001);
	animations->Add(601, ani);

	ani = new CAnimation(300);		// Goomba walk
	ani->Add(30001);
	ani->Add(30002);
	animations->Add(701, ani);

	ani = new CAnimation(1000);		// Goomba dead
	ani->Add(30003);
	animations->Add(702, ani);


	//loadMapHere
	/// Animation hoac dong theo ngan xep?
	SIMON = new CSIMON();
	SIMON->AddAnimation(400);		// idle right big   /0
	SIMON->AddAnimation(500);		// walk right big   /1
	SIMON->AddAnimation(505);		 //Idle sit right          /2
	SIMON->AddAnimation(502);		//SIMON Stand fire        /3


	SIMON->AddAnimation(506);		//Simon sit fight         /4
	SIMON->AddAnimation(507);		//Simon up whip           /5
	SIMON->AddAnimation(599);		// die  /6

	SIMON->SetPosition(100.0f, 250.0f);
	CGlobal::GetInstance()->objects.push_back(SIMON);


	

	CTorch* Torch = new CTorch();
	Torch->AddAnimation(801);
	Torch->SetPosition(0 + 450, 350 - 60);
	Torch->SetState(TORCH_STATE_BURNING);
	Torch->setItemState(ITEM_STATE_BHEART);
	CGlobal::GetInstance()->objects.push_back(Torch);


	Torch = new CTorch();
	Torch->AddAnimation(801);
	Torch->SetPosition(750, 350 - 60);
	Torch->SetState(TORCH_STATE_BURNING);
	Torch->setItemState(ITEM_STATE_NWHIP);
	CGlobal::GetInstance()->objects.push_back(Torch);



	Torch = new CTorch();
	Torch->AddAnimation(801);
	Torch->SetPosition(950, 350 - 60);
	Torch->SetState(TORCH_STATE_BURNING);
	Torch->setItemState(ITEM_STATE_NWHIP);
	CGlobal::GetInstance()->objects.push_back(Torch);



	Torch = new CTorch();
	Torch->AddAnimation(801);
	Torch->SetPosition(1200, 350 - 60);
	Torch->SetState(TORCH_STATE_BURNING);
	Torch->setItemState(ITEM_STATE_DANGER);
	CGlobal::GetInstance()->objects.push_back(Torch);


	

	for (int i = 0; i < 1536/32+4; i++)
	{
		CBrick *brick = new CBrick();
		brick->AddAnimation(601);
		brick->SetPosition(0 + i*30.0f, 350);
		CGlobal::GetInstance()->objects.push_back(brick);
	}





	// and Goombas 
	for (int i = 0; i < 4; i++)
	{
		goomba = new CGhoul();
		goomba->AddAnimation(701);
		goomba->AddAnimation(702);
		goomba->SetPosition(400 + i * 100, 350-30*2);
		goomba->SetState(GOOMBA_STATE_WALKING);
		CGlobal::GetInstance()->objects.push_back(goomba);
	}

}

/*
Update world status for this frame
dt: time period between beginning of last frame and beginning of this frame
*/
void Update(DWORD dt)
{


	// We know that SIMON is the first object in the list hence we won't add him into the colliable object list
	// TO-DO: This is a "dirty" way, need a more organized way 
	if (SIMON->x >= 640 / 2 - 60 && SIMON->x < 1530 - 640 / 2 - 60)
	{

		game->setCam(SIMON->x - SCREEN_WIDTH / 2 + 62, 0);
		CCamera::GetInstance()->isCamMove = true;
	}
	else
	{
		CCamera::GetInstance()->isCamMove = false;
	}

	vector<LPGAMEOBJECT> coObjects;
	//dọn rác trc khi update
	for (int i = 0; i < CGlobal::GetInstance()->objects.size(); i++)
	{

		if (CGlobal::GetInstance()->objects[i]->isRemove == true)
		{
			CGlobal::GetInstance()->objects.erase(CGlobal::GetInstance()->objects.begin() + i);
			DebugOut(L"==========Object bi xoa =================\n");
		}
	}
	float camX, camY;
	CCamera::GetInstance()->getCamera(camX, camY);
	for (int i = 1; i < CGlobal::GetInstance()->objects.size(); i++)
	{
		if (CGlobal::GetInstance()->objects[i]->x>(int)camX &&CGlobal::GetInstance()->objects[i]->x<(int)camX + SCREEN_WIDTH)
		{
			coObjects.push_back(CGlobal::GetInstance()->objects[i]);
		}
		
	}



	//DebugOut(L"CoObsize=%d \n Obsize=%d \n", coObjects.size(), CGlobal::GetInstance()->objects.size());
	for (int i = 0; i < CGlobal::GetInstance()->objects.size(); i++)
	{
		//-64,+64 có 1 số object nếu vượt khỏi vp sẽ xóa khỏi list,
		// nếu k + và - thêm sẽ ngừng update nên k xét đc điều kiện
		// bên trong các object
		if (CGlobal::GetInstance()->objects[i]->x>(int)camX-64 &&CGlobal::GetInstance()->objects[i]->x<(int)camX + SCREEN_WIDTH+64)
		{
			CGlobal::GetInstance()->objects[i]->Update(dt, &coObjects);
		}
		
	}
}

/*
Render a frame
*/
void Render()
{
	LPDIRECT3DDEVICE9 d3ddv = game->GetDirect3DDevice();
	LPDIRECT3DSURFACE9 bb = game->GetBackBuffer();
	LPD3DXSPRITE spriteHandler = game->GetSpriteHandler();

	if (d3ddv->BeginScene())
	{
		// Clear back buffer with a color
		d3ddv->ColorFill(bb, NULL, BACKGROUND_COLOR);

		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
		//game->Draw(0, 25, CTextures::GetInstance()->Get(ID_BACKGROUND), 0, 0, 1550, 325, 255);
		tileG->DrawMap();
		float camX, camY;
		CCamera::GetInstance()->getCamera(camX, camY);
		for (int i = 0; i < CGlobal::GetInstance()->objects.size(); i++)
		{
			if (CGlobal::GetInstance()->objects[i]->x>(int)camX-32&& CGlobal::GetInstance()->objects[i]->x<(int)camX + SCREEN_WIDTH)
			{
				CGlobal::GetInstance()->objects[i]->Render();
			}
			
		}


		spriteHandler->End();
		d3ddv->EndScene();
	}

	// Display back buffer content to the screen
	d3ddv->Present(NULL, NULL, NULL, NULL);
}

HWND CreateGameWindow(HINSTANCE hInstance, int nCmdShow, int ScreenWidth, int ScreenHeight)
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = hInstance;

	wc.lpfnWndProc = (WNDPROC)WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = WINDOW_CLASS_NAME;
	wc.hIconSm = NULL;

	RegisterClassEx(&wc);

	HWND hWnd =
		CreateWindow(
			WINDOW_CLASS_NAME,
			MAIN_WINDOW_TITLE,
			WS_OVERLAPPEDWINDOW, // WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			ScreenWidth,
			ScreenHeight,
			NULL,
			NULL,
			hInstance,
			NULL);

	if (!hWnd)
	{
		OutputDebugString(L"[ERROR] CreateWindow failed");
		DWORD ErrCode = GetLastError();
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return hWnd;
}

int Run()
{
	MSG msg;
	int done = 0;
	DWORD frameStart = GetTickCount();
	DWORD tickPerFrame = 1000 / MAX_FRAME_RATE;

	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) done = 1;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		DWORD now = GetTickCount();

		// dt: the time between (beginning of last frame) and now
		// this frame: the frame we are about to render
		DWORD dt = now - frameStart;

		if (dt >= tickPerFrame)
		{
			frameStart = now;

			game->ProcessKeyboard();

			Update(dt);
			Render();
			
		}
		else
			Sleep(tickPerFrame - dt);
	}

	return 1;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	HWND hWnd = CreateGameWindow(hInstance, nCmdShow, SCREEN_WIDTH, SCREEN_HEIGHT);

	game = CGame::GetInstance();
	game->Init(hWnd);

	keyHandler = new CSampleKeyHander();
	game->InitKeyboard(keyHandler);
	scene = CSceneManager::GetInstance();

	LoadResources();
	scene->GetInstance()->LoadResource();
	/// hien ra giua man hinh may tinh 
	// chua sua duoc


	SetWindowPos(hWnd, 0, 0, 0, SCREEN_WIDTH , SCREEN_HEIGHT , SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);

	Run();

	return 0;
}
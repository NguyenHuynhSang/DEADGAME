/* =============================================================
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

#include "Simon.h"
#include "Brick.h"
#include "Zombie.h">
#include "Torch.h"
#define WINDOW_CLASS_NAME L"CastleVania"
#define MAIN_WINDOW_TITLE L"CastleVania"
///Clear background to black
#define BACKGROUND_COLOR D3DCOLOR_XRGB(0, 0, 0)

// kích thước mặc định của Window
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

#define MAX_FRAME_RATE 120

#define ID_TEX_SIMON 0
#define ID_TEX_ENEMY 10
#define ID_TEX_MISC 20
#define ID_TEX_TORCH 30
#define ID_BACKGROUND 1000

CGame *game;

CSIMON *SIMON;
CGoomba *goomba;

vector<LPGAMEOBJECT> objects;

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
	/*case DIK_SPACE:
		SIMON->SetState(SIMON_STATE_JUMP);
		break;*/
	case DIK_A: // reset
		SIMON->SetState(SIMON_STATE_IDLE);
		SIMON->SetLevel(SIMON_LEVEL_BIG);
		SIMON->SetPosition(100.0f, 0.0f);
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
	SIMON->getStateforAniSitandJump=false;
	// code chi danh cho scene dau tien
	if (SIMON->x>=640/2-60 && SIMON->x<=1550-640/2-60)
	{

		game->setCam(SIMON->x - 640 / 2 + 60, NULL);
	}
	
	
	// disable control key when SIMON die 
	if (SIMON->GetState() == SIMON_STATE_DIE) return;

	if (game->IsKeyDown(DIK_SPACE))
	{
		SIMON->getStateforAniSitandJump = true;
		SIMON->SetState(SIMON_STATE_JUMP);
		return;
	}



//disable move when sit
	if (game->IsKeyDown(DIK_DOWN))
	{
		SIMON->getStateforAniSitandJump=true;
		// set state tranh truong hop nguoi dung bam cung luc ngoi va toi
		SIMON->SetState(SIMON_STATE_IDLE);
		return;
	}
//arrow right
	if (game->IsKeyDown(DIK_RIGHT))
	{
		SIMON->SetState(SIMON_STATE_WALKING_RIGHT);
		//isleft = false;
	}
	//arrow left	
	else if (game->IsKeyDown(DIK_LEFT))
	{
		SIMON->SetState(SIMON_STATE_WALKING_LEFT);
	//	isleft = true;
	}
		
	else
		SIMON->SetState(SIMON_STATE_IDLE);
	///Bat su kien khi simon ngoi` xuong

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

	textures->Add(ID_TEX_SIMON, L"Resource\\sprites\\SIMON.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_MISC, L"Resource\\sprites\\Ground\\2.png", D3DCOLOR_XRGB(225, 0, 248));
	textures->Add(ID_TEX_ENEMY, L"Resource\\sprites\\Enemies\\ZOMBIE.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_TORCH, L"Resource\\sprites\\Ground\\0.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_BACKGROUND, L"Resource\\sprites\\lv1.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_BBOX, L"textures\\bbox.png", D3DCOLOR_XRGB(255, 255, 255));


	CSprites * sprites = CSprites::GetInstance();
	CAnimations * animations = CAnimations::GetInstance();

	LPDIRECT3DTEXTURE9 texSimon = textures->Get(ID_TEX_SIMON);

	// big
	sprites->Add(10001, 432, 199, 470, 260, texSimon);		// idle right
	sprites->Add(10002, 374, 199, 402, 260, texSimon);		// walk
	sprites->Add(10003, 315, 199, 346, 260, texSimon);
	sprites->Add(10004, 255, 199, 286, 260, texSimon);


	sprites->Add(10011, 11, 3, 46, 64, texSimon);		// idle left
	sprites->Add(10012, 76, 3, 105, 64, texSimon);		// walk
	sprites->Add(10013, 133, 3, 167, 64, texSimon);
	sprites->Add(10014, 193, 3, 222, 64, texSimon);


	sprites->Add(10015, 252, 3, 283, 65, texSimon);//Simon sit left
	sprites->Add(10016, 194, 199, 229, 262, texSimon);//Simon sit Right



	sprites->Add(10099, 215, 120, 231, 135, texSimon);		// die 

	//torch
	LPDIRECT3DTEXTURE9 texTch = textures->Get(ID_TEX_TORCH);
	sprites->Add(40000,0,0,32,64, texTch);
	sprites->Add(40001, 32, 0, 64, 64, texTch);
	//														// small
	//sprites->Add(10021, 247, 0, 259, 15, texSimon);			// idle small right
	//sprites->Add(10022, 275, 0, 291, 15, texSimon);			// walk 
	//sprites->Add(10023, 306, 0, 320, 15, texSimon);			// 

	//sprites->Add(10031, 187, 0, 198, 15, texSimon);			// idle small left

	//sprites->Add(10032, 155, 0, 170, 15, texSimon);			// walk
	//sprites->Add(10033, 125, 0, 139, 15, texSimon);			// 


	LPDIRECT3DTEXTURE9 texMisc = textures->Get(ID_TEX_MISC);
	sprites->Add(20001, 0, 0, 30, 30, texMisc);

	///Load texZombie here
	LPDIRECT3DTEXTURE9 texEnemy = textures->Get(ID_TEX_ENEMY);
	sprites->Add(30001, 0, 0, 34, 63, texEnemy);
	sprites->Add(30002, 31, 0, 65, 63, texEnemy);

	sprites->Add(30003, 45, 21, 61, 29, texEnemy); // die sprite




	LPANIMATION ani;

	ani = new CAnimation(100);	// idle big right
	ani->Add(10001);
	animations->Add(400, ani);

	ani = new CAnimation(100);	// idle big left
	ani->Add(10011);
	animations->Add(401, ani);

	//ani = new CAnimation(100);	// idle small right
	//ani->Add(10021);
	//animations->Add(402, ani);

	//ani = new CAnimation(100);	// idle small left
	//ani->Add(10031);
	//animations->Add(403, ani);

	ani = new CAnimation(100);	// walk right big
	ani->Add(10001);
	ani->Add(10002);
	ani->Add(10003);
	ani->Add(10004);
	animations->Add(500, ani);

	ani = new CAnimation(100);	// // walk left big
	ani->Add(10011);
	ani->Add(10012);
	ani->Add(10013);
	ani->Add(10014);
	animations->Add(501, ani);

	//ani = new CAnimation(100);	// walk right small
	//ani->Add(10021);
	//ani->Add(10022);
	//ani->Add(10023);
	//animations->Add(502, ani);

	//ani = new CAnimation(100);	// walk left small
	//ani->Add(10031);
	//ani->Add(10032);
	//ani->Add(10033);
	//animations->Add(503, ani);

	ani = new CAnimation(100); //simon sit left
	ani->Add(10015);
	animations->Add(504, ani);

	ani = new CAnimation(100); //simon sit right
	ani->Add(10016);
	animations->Add(505, ani);



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


	for (int i = 0; i < 10; i++)
	{
		CTorch* Torch = new CTorch();
		Torch->AddAnimation(801);
		Torch->SetPosition(0 + i*300.0f, 350 - 60);
		Torch->SetState(TORCH_STATE_BURNING);
		objects.push_back(Torch);
	}
	/// Animation hoac dong theo ngan xep?
	SIMON = new CSIMON();
	SIMON->AddAnimation(400);		// idle right big   /0
	SIMON->AddAnimation(401);		// idle left big    /1
	SIMON->AddAnimation(500);		// walk right big   /2
	SIMON->AddAnimation(501);		// walk left big    /3
	SIMON->AddAnimation(504); //Idle sit left           /4
	SIMON->AddAnimation(505); //Idle sit right          /5


	SIMON->AddAnimation(599);		// die

	SIMON->SetPosition(100.0f, 0);
	objects.push_back(SIMON);
	
	//for (int i = 0; i < 5; i++)
	//{
	//	CBrick *brick = new CBrick();
	//	brick->AddAnimation(601);
	//	brick->SetPosition(100 + i*48.0f, 74);
	//	objects.push_back(brick);

	//	brick = new CBrick();
	//	brick->AddAnimation(601);
	//	brick->SetPosition(100 + i*48.0f, 90);
	//	objects.push_back(brick);

	//	brick = new CBrick();
	//	brick->AddAnimation(601);
	//	brick->SetPosition(84 + i*48.0f, 90);
	//	objects.push_back(brick);
	//}


	for (int i = 0; i < 100; i++)
	{
		CBrick *brick = new CBrick();
		brick->AddAnimation(601);
		brick->SetPosition(0 + i*30.0f, 350);
		objects.push_back(brick);
	}





	// and Goombas 
	for (int i = 0; i < 4; i++)
	{
		goomba = new CGoomba();
		goomba->AddAnimation(701);
		goomba->AddAnimation(702);
		goomba->SetPosition(200 + i * 60, 350-30*2);
		goomba->SetState(GOOMBA_STATE_WALKING);
		objects.push_back(goomba);
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
	vector<LPGAMEOBJECT> coObjects;
	for (int i = 1; i < objects.size(); i++)
	{
		coObjects.push_back(objects[i]);
	}

	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->Update(dt, &coObjects);
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
		game->Draw(0, 25, CTextures::GetInstance()->Get(ID_BACKGROUND), 0, 0, 1550, 325, 255);

		for (int i = 0; i < objects.size(); i++)
			objects[i]->Render();

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


	LoadResources();
	/// hien ra giua man hinh may tinh 


	SetWindowPos(hWnd, 0, 0, 0, SCREEN_WIDTH , SCREEN_HEIGHT , SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);

	Run();

	return 0;
}
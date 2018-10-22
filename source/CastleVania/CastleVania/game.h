#pragma once
#include<d3d9.h>
#include<d3dx9.h>
#include<Windows.h>
#include"graphics.h"
#include"Textures.h"
#include"Sprites.h"
#include"Objects.h"
class CGame
{
	static CGame * __instance;
	HWND hWnd;
	graphics *graphic;
public:
	//create a graphic device here,input and sound here too,
	//sorry my poor english
	void Init(HWND hwnd);
	void Draw();
	void render();
	void GameRun(HWND _hwnd);
	void GameUpdate(HWND _hwnd);
	void GameEnd(HWND _hwnd);
	// load resource 1 lần ==> xử lý nhanh hơn nhưng nặng máy
	//==> có thể tạo lớp resource để quản lý
	// bổ xung sau
	void LoadResource();
	static CGame * GetInstance();	
	void backbuffer();
	CGame();
	~CGame();
};


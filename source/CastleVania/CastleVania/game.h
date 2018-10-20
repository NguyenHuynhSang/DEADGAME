#pragma once
#include<d3d9.h>
#include<d3dx9.h>
#include<Windows.h>
#include"graphics.h"
class CGame
{
	static CGame * __instance;
	HWND hWnd;
	graphics *graphic;
public:
	void Init();
	void GameRun(HWND _hwnd);
	void GameUpdate(HWND _hwnd);
	void GameEnd(HWND _hwnd);
	static CGame * GetInstance();
	CGame();
	~CGame();
};


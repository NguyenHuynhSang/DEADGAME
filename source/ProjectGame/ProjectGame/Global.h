#pragma once
#include"Game.h"
#include"GameObject.h"
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
class CGlobal
{
public:
	vector<LPGAMEOBJECT> objects;
	static CGlobal * GetInstance();
	 bool isShowItem = false;
	CGlobal();
	~CGlobal();
private:
	
	static	CGlobal	*__instance;
};


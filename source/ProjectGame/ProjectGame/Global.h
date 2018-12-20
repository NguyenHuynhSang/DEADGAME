#pragma once
#include"Game.h"
#include"GameObject.h"
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define ID_TEX_SIMON 0
#define ID_TEX_ENEMY 10
#define ID_TEX_BRICK 20
#define ID_TEX_TORCH 30
#define ID_TEX_EFFECT 60
#define ID_TEX_BAT   70
#define ID_TEX_FISHMAN 80
#define ID_TEX_BLACKBOARD 90

#define ID_TEX_DOOR_LV1  200
#define ID_TEX_DOOR_LV2  210
#define ID_TEX_PANTHER              100

#define ID_BACKGROUND_LV1 1000
#define ID_BACKGROUND_LV2 2000
#define ID_BACKGROUND_LV3 3000

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


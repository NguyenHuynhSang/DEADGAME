#pragma once
#include"Game.h"
#include"GameObject.h"
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


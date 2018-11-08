//#pragma once
//#include<d3d9.h>
//#include<d3dx9.h>
//#include<Windows.h>
//#include"debug.h"
//#include"Sprites.h"
//class CanimationFrame
//{
//	LPSPRITE sprite;
//	DWORD time;	
//public:
//	CanimationFrame(LPSPRITE sprite, int time) { this->sprite = sprite; this->time = time; }
//	DWORD GetTime() { return time; }
//	LPSPRITE GetSprite() { return sprite; }
//	//CanimationFrame();
//	//~CanimationFrame();
//};
//typedef CanimationFrame *LPANIMATION_FRAME;
//class CAnimation
//{
//	DWORD lastFrameTime;
//	int defaultTime;
//	int currentFrame;
//	vector<LPANIMATION_FRAME> frames;
//public:
//	CAnimation(int defaultTime) { this->defaultTime = defaultTime; lastFrameTime = -1; currentFrame = -1; }
//	void Add(int spriteId, DWORD time = 0);
//	void Render(float x, float y, int alpha = 255);
//};
//
//typedef CAnimation *LPANIMATION;
//class CAnimations
//{
//	
//	static CAnimations * __instance;
//	unordered_map<int, LPANIMATION> animations;
//
//public:
//	void Add(int id, LPANIMATION ani);
//	LPANIMATION Get(int id);
//
//	static CAnimations * GetInstance();
//};
//
//

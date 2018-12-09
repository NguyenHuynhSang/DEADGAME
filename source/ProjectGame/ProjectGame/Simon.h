#pragma once
#include "GameObject.h"
#include"Whip.h"
#include"Textures.h"
#include"Dagger.h"
#define SIMON_WALKING_SPEED		0.15f 
#define SIMON_FIRE_TIME			300
//0.1f
#define SIMON_JUMP_SPEED_Y		0.55f
#define SIMON_JUMP_DEFLECT_SPEED 0.2f
#define SIMON_GRAVITY			0.002f
#define SIMON_DIE_DEFLECT_SPEED	 0.5f

//Simon State

#define SIMON_STATE_IDLE			0
#define SIMON_STATE_WALKING_RIGHT	100
#define SIMON_STATE_WALKING_LEFT	200
#define SIMON_STATE_JUMP			300
#define SIMON_STATE_DIE				400
#define SIMON_STATE_SIT             500
#define SIMON_STATE_STAND_FIGHTING			600
#define SIMON_STATE_SIT_FIGHTING			700
#define SIMON_STATE_UPWHIP                  800

#define SIMON_ANI_IDLE		0
#define SIMON_ANI_WALKING			1
#define SIMON_ANI_SIT_JUMP            2 // sit and jump have same ani
#define SIMON_ANI_STAND_FIRE				3
#define SIMON_ANI_SIT_FIRE					4
#define SIMON_ANI_UPWHIP     5
#define SIMON_ANI_DIE				8


#define SIMON_BIG_BBOX_WIDTH  30
#define SIMON_BIG_BBOX_HEIGHT 60

#define SIMON_MAX_LIFE_BAR 20
#define SIMON_MAX_HEART_BAR 20



// có thể sửa lại thành invisible 
#define SIMON_UNTOUCHABLE_TIME 5000







class CSIMON : public CGameObject
{
	static CSIMON *__instance;
	int untouchable;
	DWORD untouchable_start;
	CWhip* whip;
	CDagger* dagger;
	int nLife;
	int nHeart;
public:



	bool isUsesW=false;
	bool isDelay = false;
	bool isUpWhip=false;
	bool isFighting = false;
	bool isSitting = false;
	bool isTouchGr() { return vy == 0 ? true : false; };

	void setLife(int _life) { nLife = nLife + _life > SIMON_MAX_LIFE_BAR ? SIMON_MAX_LIFE_BAR : nLife + _life; }
	int getLife() { return nLife; }
	void setHeart(int _heart){ nHeart = nHeart + _heart > SIMON_MAX_LIFE_BAR ? SIMON_MAX_LIFE_BAR : nHeart + _heart; }
	int getHeart(){ return nHeart; }
	static CSIMON *GetInstance();
	CSIMON() 
	{
		LoadResource();
		AddAnimation(400);		// idle right big   /0
		AddAnimation(500);		// walk right big   /1
		AddAnimation(505);		 //Idle sit right          /2
		AddAnimation(502);		//SIMON Stand fire        /3
		AddAnimation(506);		//Simon sit fight         /4
		AddAnimation(507);		//Simon up whip           /5
		AddAnimation(599);		// die  /6

		nLife = SIMON_MAX_LIFE_BAR;
		nHeart = 0;
		untouchable = 0;
		whip = new CWhip();
	}
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	virtual void Render();
	virtual void LoadResource();
	bool isJump=false;
	void SetState(int state);
	//void SetLevel(int l) { level = l; }
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);


	
};
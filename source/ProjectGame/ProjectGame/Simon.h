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
#define SIMON_STATE_UP_STAIR                1000
#define SIMON_STATE_DOWN_STAIR              1100
#define SIMON_STATE_IDLE_UP_STAIR           1200
#define SIMON_STATE_IDLE_DOWN_STAIR           1300

#define SIMON_ANI_IDLE              		0
#define SIMON_ANI_WALKING			        1
#define SIMON_ANI_SIT_JUMP                  2 // sit and jump have same ani
#define SIMON_ANI_STAND_FIRE				3
#define SIMON_ANI_SIT_FIRE					4
#define SIMON_ANI_UPWHIP                    5
#define SIMON_ANI_UPSTAIR                   6
#define SIMON_ANI_DOWNSTAIR                 7
#define SIMON_ANI_IDLE_UPSTAIR              8
#define SIMON_ANI_IDLE_DOWNSTAIR            9
#define SIMON_ANI_DIE				50


#define SIMON_BIG_BBOX_WIDTH  30
#define SIMON_BIG_BBOX_HEIGHT 60

#define SIMON_MAX_LIFE_BAR 20
#define SIMON_MAX_HEART_BAR 20

#define SIMON_IDANI_IDLE  400
#define SIMON_IDANI_WALKING  500
#define SIMON_IDANI_SITTING  505
#define SIMON_IDANI_STANDFIGHT  502
#define SIMON_IDANI_SITFIGHT  506
#define SIMON_IDANI_UPWHIP  507
#define SIMON_IDANI_WUPSTAIR  508
#define SIMON_IDANI_WDOWNSTAIR  509
#define SIMON_IDANI_IDLEUSTAIR  510
#define SIMON_IDANI_IDLEDSTAIR  511
// có thể sửa lại thành invisible 
#define SIMON_UNTOUCHABLE_TIME 5000

#define SIMON_ONSTAIR_TIME 100





class CSIMON : public CGameObject
{
	static CSIMON *__instance;
	int untouchable;
	DWORD untouchable_start;
	CWhip* whip;
	CDagger* dagger;
	int nLife;
	int nHeart;
	int currentSubWeapon = 0;
public:

	bool isUsesW = false;
	bool isDelay = false;
	bool isUpWhip = false;
	bool isFighting = false;
	bool isSitting = false;
	bool isUpStair = false;
	bool isDownStair = false;
	bool topStair = false;
	bool bottomStair = false;
	bool onStair = false;
	int stair_X = 0;
	int stairState = 0;
	bool autoWalk = false;
	bool isTouchGr() { return vy == 0 ? true : false; };
	void setLife(int _life) { nLife = nLife + _life > SIMON_MAX_LIFE_BAR ? SIMON_MAX_LIFE_BAR : nLife + _life; }
	int getLife() { return nLife; }
	void setHeart(int _heart) { nHeart = nHeart + _heart > SIMON_MAX_LIFE_BAR ? SIMON_MAX_LIFE_BAR : nHeart + _heart; }
	int getHeart() { return nHeart; }
	int getcurrentSubWeapon() { return currentSubWeapon; };
	void setNX(float x) { nx = x; }
	static CSIMON *GetInstance();
	CSIMON() 
	{
		LoadResource();
		AddAnimation(SIMON_IDANI_IDLE);		// idle                   /0
		AddAnimation(SIMON_IDANI_WALKING);		// walk                   /1
		AddAnimation(SIMON_IDANI_SITTING);		// sit                    /2
		AddAnimation(SIMON_IDANI_STANDFIGHT);		//SIMON Stand fire        /3
		AddAnimation(SIMON_IDANI_SITFIGHT);		//Simon sit fight         /4
		AddAnimation(SIMON_IDANI_UPWHIP);		//Simon up whip           /5
		AddAnimation(SIMON_IDANI_WUPSTAIR);      //Simon walking up stair          /6
		AddAnimation(SIMON_IDANI_WDOWNSTAIR);      //Simon walking down stair          /7
		AddAnimation(SIMON_IDANI_IDLEUSTAIR);      //Simon idle up stair     /8
		AddAnimation(SIMON_IDANI_IDLEDSTAIR);      //Simon idle down stair   /9
		AddAnimation(599);		// die  /200

		nLife = SIMON_MAX_LIFE_BAR;
		nHeart = 50;
		untouchable = 0;
		whip = CWhip::GetInstance();
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
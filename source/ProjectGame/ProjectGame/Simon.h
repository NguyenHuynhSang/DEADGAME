#pragma once
#include "GameObject.h"
#include"Whip.h"
#include"Textures.h"
#define SIMON_WALKING_SPEED		0.15f 
#define SIMON_FIRE_TIME			300
//0.1f
#define SIMON_JUMP_SPEED_Y		0.54f
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
#define SIMON_STAGE_STAND_FIGHTING			600
#define SIMON_STAGE_SIT_FIGHTING			700


#define SIMON_ANI_BIG_IDLE		0
#define SIMON_ANI_BIG_WALKING			1
#define SIMON_ANI_SIT_JUMP            2
#define SIMON_ANI_STAND_FIRE				3
#define SIMON_ANI_SIT_FIRE					4
#define SIMON_ANI_DIE				8

#define	SIMON_LEVEL_SMALL	1
#define	SIMON_LEVEL_BIG		2

#define SIMON_BIG_BBOX_WIDTH  30
#define SIMON_BIG_BBOX_HEIGHT 60
//
//#define SIMON_SMALL_BBOX_WIDTH  13
//#define SIMON_SMALL_BBOX_HEIGHT 15

// có thể sửa lại thành invisible 
#define SIMON_UNTOUCHABLE_TIME 5000






class CSIMON : public CGameObject
{
	int level;
	int untouchable;
	DWORD untouchable_start;
	CWhip* whip;
	DWORD setTimeforDelay;

public:
	bool isFighting = false;
	CSIMON() : CGameObject()
	{
		level = SIMON_LEVEL_BIG;

		whip = new CWhip();
		untouchable = 0;
		CSprites * sprites = CSprites::GetInstance();
		CAnimations * animations = CAnimations::GetInstance();

		CTextures * textures = CTextures::GetInstance();

		LPDIRECT3DTEXTURE9 texWhip = textures->Get(55);

		sprites->Add(20001, 0, 0, 240, 66, texWhip); // normal whip
		sprites->Add(20002, 240, 0, 480, 66, texWhip);
		sprites->Add(20003, 480, 0, 720, 66, texWhip);
		sprites->Add(20004, 0, 1, 2, 3, texWhip);

		LPANIMATION ani;
		ani = new CAnimation(150); //WHIP ani
		ani->Add(20001);
		ani->Add(20002);
		ani->Add(20003);
		ani->Add(20004);
		animations->Add(555, ani);
		whip->AddAnimation(555);




	}
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	virtual void Render();

	bool getStateforAniSitandJump=false;
	void SetState(int state);
	void SetLevel(int l) { level = l; }
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);


	
};
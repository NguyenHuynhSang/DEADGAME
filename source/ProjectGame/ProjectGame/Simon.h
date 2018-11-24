#pragma once
#include "GameObject.h"
#include"Whip.h"
#include"Textures.h"
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
	int untouchable;
	DWORD untouchable_start;
	CWhip* whip;
	int nLife;
	int nHeart;
public:




	bool isUpWhip=false;
	bool isFighting = false;
	bool isSitting = false;
	bool isTouchGr() { return vy == 0 ? true : false; };

	void setLife(int _life) { nLife = nLife + _life > SIMON_MAX_LIFE_BAR ? SIMON_MAX_LIFE_BAR : nLife + _life; }
	int getLife() { return nLife; }
	void setHeart(int _heart){ nHeart = nHeart + _heart > SIMON_MAX_LIFE_BAR ? SIMON_MAX_LIFE_BAR : nHeart + _heart; }
	int getHeart(){ return nHeart; }

	CSIMON() : CGameObject()
	{
		nLife = SIMON_MAX_LIFE_BAR;
		nHeart = 0;
		untouchable = 0;


#pragma region whip
		whip = new CWhip();

		CSprites * sprites = CSprites::GetInstance();
		CAnimations * animations = CAnimations::GetInstance();

		CTextures * textures = CTextures::GetInstance();

		LPDIRECT3DTEXTURE9 texWhip = textures->Get(ID_TEX_WHIP);

		sprites->Add(20001, 0, 0, 240, 66, texWhip); // normal whip
		sprites->Add(20002, 240, 0, 480, 66, texWhip);
		sprites->Add(20003, 480, 0, 720, 66, texWhip);
		sprites->Add(20004, 0, 1, 2, 3, texWhip);

		sprites->Add(20005, 0, 66, 240, 132, texWhip); // Blue Whip
		sprites->Add(20006, 240, 66, 480, 132, texWhip);
		sprites->Add(20007, 480, 66, 720, 132, texWhip);


		sprites->Add(20008, 0, 132, 240, 198, texWhip); // Red whip
		sprites->Add(20009, 240, 132, 480, 198, texWhip);
		sprites->Add(20010, 480, 132, 720, 198, texWhip);
		sprites->Add(20011, 0, 198, 240, 264, texWhip);

		sprites->Add(20012, 240, 198, 480, 264, texWhip);
		sprites->Add(20013, 480, 198, 720, 264, texWhip);
		sprites->Add(20014, 0, 264, 240, 330, texWhip);
		sprites->Add(20015, 240, 264, 480, 330, texWhip);

		sprites->Add(20016, 480, 264, 720, 330, texWhip);
		sprites->Add(20017, 0, 330, 240, 396, texWhip);
		sprites->Add(20018, 240, 330, 480, 396, texWhip);
		sprites->Add(20019, 480, 330, 720, 396, texWhip);
		sprites->Add(20020, 0, 0, 1, 1, texWhip);
		LPANIMATION ani;

		ani = new CAnimation(WHIP_DELAY_TIME); //NOLMAL WHIP
		ani->Add(20001);
		ani->Add(20002);
		ani->Add(20003);
		ani->Add(20004);
		animations->Add(WHIP_NOLMAL_ANI_ID, ani);



		ani = new CAnimation(WHIP_DELAY_TIME); //BLUE WHIP
		ani->Add(20005);
		ani->Add(20006);
		ani->Add(20007);
		ani->Add(20004);
		animations->Add(WHIP_BLUE_ANI_ID, ani);

		ani = new CAnimation(8); //red WHIP

		ani->Add(20008);
		ani->Add(20009);
		ani->Add(20010);

		ani->Add(20011);
		ani->Add(20012);
		ani->Add(20013);

		ani->Add(20014);
		ani->Add(20015);
		ani->Add(20016);

		ani->Add(20017);
		ani->Add(20018);
		ani->Add(20019);

		ani->Add(20020);
		animations->Add(WHIP_RED_ANI_ID, ani);



		whip->AddAnimation(WHIP_NOLMAL_ANI_ID); //Nomal Whip /0
		whip->AddAnimation(WHIP_BLUE_ANI_ID); //blue whip /1
		whip->AddAnimation(WHIP_RED_ANI_ID); //red 2
#pragma endregion 

#pragma region Dagger




#pragma endregion


		
	}
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	virtual void Render();

	bool getStateforAniSitandJump=false;
	void SetState(int state);
	//void SetLevel(int l) { level = l; }
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);


	
};
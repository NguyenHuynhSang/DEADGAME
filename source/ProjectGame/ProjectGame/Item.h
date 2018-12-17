#pragma once
#include"GameObject.h"

#define ITEM_GRAVITY 0.002f
#define ITEM_SHOW_TIME 3000



#define ID_TEX_ITEM_BHEART 200
#define ID_TEX_ITEM_NWHIP 201
#define ID_TEX_ITEM_DANGER 202
#define ID_TEX_ITEM_MHEART 203
#define ID_TEX_ITEM_WHITE_MONEYBAG 204
#define ID_TEX_ITEM_BLUE_MONEYBAG 205
#define ID_TEX_ITEM_RED_MONEYBAG 206

#define ITEM_STATE_NWHIP 0
#define ITEM_STATE_BHEART 1
#define ITEM_STATE_DANGER 2
#define ITEM_STATE_MHEART 3
#define ITEM_STATE_WHITE_MONEYBAG 4
#define ITEM_STATE_BLUE_MONEYBAG 5
#define ITEM_STATE_RED_MONEYBAG 6



#define BHEART_BBOX_BIG_WIDTH	24
#define BHEART_BBOX_BIG_HEIGHT	20

#define MHEART_BBOX_WIDTH	16
#define MHEART_BBOX_HEIGHT	16


#define DAGGER_BBOX_WIDTH	32
#define DAGGER_BBOX_HEIGHT	18

#define WHIP_UPDATE_BBOX_WIDTH 32
#define WHIP_UPDATE_BBOX_HEIGHT 32


#define MONEYBAG_BBOX_WIDTH 30
#define MONEYBAG_BBOX_HEIGHT 30


class CItem:public CGameObject
{
	DWORD timeStart;
	DWORD timeShow;
public:
	bool isShow = false;
	bool colSimon = false;
	virtual void Render();
	void createItem();
	int _rank();
	virtual void LoadResource();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* co);	
//	virtual void SetState(int state);

	CItem();
	~CItem();
};


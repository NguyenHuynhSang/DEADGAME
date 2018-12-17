#pragma once
#include"GameObject.h"

#define ITEM_GRAVITY 0.002f
#define ITEM_SHOW_TIME 3000



#define ID_TEX_ITEM_BHEAR 200
#define ID_TEX_ITEM_NWHIP 201
#define ID_TEX_ITEM_DANGER 202


#define ITEM_STATE_BHEART 0
#define ITEM_STATE_DANGER 1
#define ITEM_STATE_NWHIP 2
#define ITEM_STATE_MHEART 3


#define BHEART_BBOX_BIG_WIDTH	24
#define BHEART_BBOX_BIG_HEIGHT	20

#define MHEART_BBOX_WIDTH	8
#define MHEART_BBOX_HEIGHT	9


#define DAGGER_BBOX_WIDTH	32
#define DAGGER_BBOX_HEIGHT	18

#define WHIP_UPDATE_BBOX_WIDTH 32
#define WHIP_UPDATE_BBOX_HEIGHT 32


class CItem:public CGameObject
{
	DWORD timeStart;
	DWORD timeShow;
public:
	bool isShow = false;
	bool colSimon = false;
	virtual void Render();
	void createItem();
	void _rank();
	virtual void LoadResource();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* co);	
//	virtual void SetState(int state);

	CItem();
	~CItem();
};


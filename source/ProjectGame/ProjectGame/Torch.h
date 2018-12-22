#pragma once
#include"GameObject.h"
#include"Item.h"
#include"Textures.h"
#include"Global.h"
#include"Effect.h"
#define TORCH_BBOX_WIDTH  30
#define TORCH_BBOX_HEIGHT  60

#define CANDLE_BBOX_WIDTH     15
#define CANDLE_BBOX_HEIGHT    32


#define TORCH_STATE_BIG 100
#define TORCH_STATE_SMAIL 200
#define TORCH_STATE_DISAPPEAR 300
#define TORCH_ANI_BIG 0
#define TORCH_ANI_SMAIL 1


class CTorch:public CGameObject
{
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render();
	CItem *item;
	CEffect *eff;
	int ItemState;
public:
	void setItemState(int nstate);
	virtual void SetState(int state);
	virtual void LoadResource();
	bool candle = false;
	CTorch() :CGameObject()
	{	
		
		ItemState = 0;
		AddAnimation(801);
		AddAnimation(802);
		eff = new CEffect();
	};
	//~CTorch();
};


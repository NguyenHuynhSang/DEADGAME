#pragma once
#include"GameObject.h"
#include"Item.h"
#include"Textures.h"
#include"Global.h"
#define TORCH_BBOX_WIDTH  30
#define TORCH_BBOX_HEIGHT  60

#define TORCH_STATE_BURNING 100
#define TORCH_STATE_DISTROY 200
#define TORCH_STATE_DISAPPEAR 300
#define TORCH_ANI_BURNING 0
#define TORCH_ANI_DESTROY 1


class CTorch:public CGameObject
{
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render();
	CItem *item;

public:
	void setItemState(int nstate);
	virtual void SetState(int state);
	CTorch() :CGameObject()
	{	
		item = new CItem(); 
	};
	//~CTorch();
};


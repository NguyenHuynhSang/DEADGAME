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

		CSprites * sprites = CSprites::GetInstance();
		CAnimations * animations = CAnimations::GetInstance();

		CTextures * textures = CTextures::GetInstance();
		LPDIRECT3DTEXTURE9 texBHear = textures->Get(ID_TEX_ITEM_BHEAR);
		sprites->Add(70000, 0, 0, 24, 20, texBHear);
		LPDIRECT3DTEXTURE9 texDanger = textures->Get(ID_TEX_ITEM_DANGER);
		sprites->Add(70001, 0, 0, 24, 20, texDanger);
		PDIRECT3DTEXTURE9 texNWhip = textures->Get(ID_TEX_ITEM_NWHIP);
		sprites->Add(70002, 0, 0, 32, 32, texNWhip);
		LPANIMATION ani;
		
		ani = new CAnimation(10000);		// BHEART
		ani->Add(70000);
		animations->Add(901, ani);

		ani = new CAnimation(100);		// danger
		ani->Add(70001);
		animations->Add(902, ani);

		ani = new CAnimation(100);		// NWhip
		ani->Add(70002);
		animations->Add(903, ani);

		item->AddAnimation(901);
		item->AddAnimation(902);
		item->AddAnimation(903);
		//carefull
		item->GetPosition(x, y);
		//thêm vào object mới có thể update, hay bắt sự kiện va chạm
		//vì cái coobject dc lay ra tu object
		//k thêm vào lấy đâu ra mà xét.
		CGlobal::GetInstance()->objects.push_back(item);

	
	};
	//~CTorch();
};


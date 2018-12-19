#include "ghoul.h"
#include"Textures.h"
#include"Global.h"
#include"HiddenObjects.h"
void CGhoul::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	right = x + GHOUL_BBOX_WIDTH;

	if (state == GHOUL_STATE_DIE)
		bottom = y + GHOUL_BBOX_HEIGHT_DIE;
	else
		bottom = y + GHOUL_BBOX_HEIGHT;
}


void CGhoul::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	CGameObject::Update(dt);
	//
	// TO-DO: make sure Goomba can interact with the world and to each of them too!
	// 
	if (state==GHOUL_STATE_DIE)
	{
		item = new CItem();

		item->_rank();
		item->SetPosition(x, y);
		CGlobal::GetInstance()->objects.push_back(item);
	
		this->isRemove = true;
		return;
	}
	
	vy += 0.002*dt;
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEventsResult.clear();
	coEvents.clear();
	CalcPotentialCollisions(coObjects, coEvents);
	for (int i = 0; i < coEvents.size(); i++)
	{
		if (dynamic_cast<CHiddenObjects *>(coEvents[i]->obj))
		{
			coEvents.erase(coEvents.begin() + i);
		}
	}
	if (coEvents.size() == 0)
	{
		y += dy;
		x += dx;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
		y += min_ty*dy + ny*0.4f;
		x += dx;
		if (ny != 0) vy = 0;
	}
	// clean up collision events
	for (int i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void CGhoul::Render()
{
	int ani = GHOUL_ANI_WALKING;
	if (state == GHOUL_STATE_DIE) {
		return;
	}

	animations[ani]->Render(-1,x, y);
	RenderBoundingBox(x,y);
}

void CGhoul::LoadResource()
{
	CSprites * sprites = CSprites::GetInstance();
	CAnimations * animations = CAnimations::GetInstance();
	CTextures * textures = CTextures::GetInstance();
	textures->Add(ID_TEX_ENEMY, L"Resource\\sprites\\Enemies\\ZOMBIE.png", D3DCOLOR_XRGB(255, 0, 255));

	///Load texZombie here
	LPDIRECT3DTEXTURE9 texEnemy = textures->Get(ID_TEX_ENEMY);
	sprites->Add(30001, 0, 0, 34, 63, texEnemy);
	sprites->Add(30002, 31, 0, 65, 63, texEnemy);

	sprites->Add(30003, 45, 21, 61, 29, texEnemy); // die sprite


	LPANIMATION ani;
	ani = new CAnimation(300);		// Goomba walk
	ani->Add(30001);
	ani->Add(30002);
	animations->Add(701, ani);

	ani = new CAnimation(1000);		// Goomba dead
	ani->Add(30003);
	animations->Add(702, ani);


}

void CGhoul::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case GHOUL_STATE_DIE:
		vx = 0;
		vy = 0;
		break;
	case GHOUL_STATE_WALKING:
		vx = -GHOUL_WALKING_SPEED;
	}

}

CGhoul::CGhoul()
{
	AddAnimation(701);
	AddAnimation(702);		

}

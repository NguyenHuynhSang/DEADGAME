#include "Dagger.h"
#include"Camera.h"
#include"ghoul.h"
#include"Torch.h"
#include"debug.h"
void CDagger::Render()
{

		animations[state]->Render(-nx, x, y);
		//RenderBoundingBox(x,y);
	
}

void CDagger::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = left + DAGGER_BBOX_WIDTH;
	bottom = top + DAGGER_BBOX_HEIGHT;
}

void CDagger::Update(DWORD dt, vector<LPGAMEOBJECT>* co)
{
	float camX, camY;
	CCamera::GetInstance()->getCamera(camX,camY);
	if (x<(int)camX|| x>(int)camX + SCREEN_WIDTH)
	{
		isRemove = true;
		DebugOut(L"Dagger Deleted \n");
		return;
	}
	vx = DAGGER_SPEED;
	if (nx<0)
	{
		vx = -vx;
	}
	
	CGameObject::Update(dt);

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();
	coEventsResult.clear();
	CalcPotentialCollisions(co, coEvents);
	if (coEvents.size() == 0)
	{
		x += dx;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
		bool isre = false;
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			//xu ly va cham 
			if (dynamic_cast<CTorch *>(e->obj))
			{
				CTorch * f = dynamic_cast<CTorch*> (e->obj);
				if (e->nx!=0)
				{
					f->SetState(TORCH_STATE_DISAPPEAR);
					//DebugOut(L"\nChay vao day");
					this->isRemove = true;
					isre = true;
				}
	
			}
			else if (dynamic_cast<CGhoul *>(e->obj))
			{
				CGhoul * g = dynamic_cast<CGhoul*> (e->obj);
				if (e->nx != 0)
				{
					g->isRemove = true;
					//DebugOut(L"\nChay vao day");
					this->isRemove = true;
					isre = true;
				}

			}
			else 
			{
				x += dx;
			}
			
			if (isre==true)
			{
				break;
			}
		}
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];


	//for (int i = 0; i < co->size(); i++)
	//{
	//	if (this->isRemove==true)
	//	{
	//		break;
	//	}
	//	LPGAMEOBJECT e = co->at(i);
	//	if (dynamic_cast<CTorch *>(e))
	//	{
	//		CTorch * f = dynamic_cast<CTorch*> (e);
	//		if (CGameObject::isColliding(this, f) == true)
	//		{

	//			DebugOut(L"Co va cham \n");
	//			f->SetState(TORCH_STATE_DISAPPEAR);
	//		
	//		}
	//	}
	//}
	//// clean up collision events
}

void CDagger::LoadResource()
{
	

	CSprites * sprites = CSprites::GetInstance();
	CAnimations * animations = CAnimations::GetInstance();
	CTextures * textures = CTextures::GetInstance();
	LPDIRECT3DTEXTURE9 texDanger = textures->Get(202);
	sprites->Add(70001, 0, 0, 32, 18, texDanger);
	LPANIMATION ani;

	ani = new CAnimation(100);		// danger
	ani->Add(70001);
	animations->Add(902, ani);
}

CDagger::CDagger()
{

	this->AddAnimation(902);
	//carefull
	//item->GetPosition(x, y);
	//thêm vào object mới có thể update, hay bắt sự kiện va chạm
	//vì cái coobject dc lay ra tu object
	//k thêm vào lấy đâu ra mà xét.
}


CDagger::~CDagger()
{



}

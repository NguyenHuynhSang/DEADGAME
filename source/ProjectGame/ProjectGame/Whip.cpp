#include "Whip.h"	
#include"Torch.h"
#include"Debug.h"
#include"Item.h"
#include"ghoul.h"
#include "Panther.h"

CWhip * CWhip::__instance = NULL;

CWhip *CWhip::GetInstance()
{
	if (__instance == NULL) __instance = new CWhip();
	return __instance;
}
void CWhip::Render()
{
	if (state == WHIP_STATE_RED)
	{
		if (CAnimations::GetInstance()->Get(WHIP_RED_ANI_ID)->getCurrentFrame() != 11)
		{
			animations[state]->Render(nx, x, y);
			if (nx>0)
			{
			//	RenderBoundingBox(220 - WHIP_RED_BBOX_WIDTH + x, y + 15);
			}
			else
			{
				//RenderBoundingBox(x+25, y + 15);
			}
			
		}
	}
	else
	{
		animations[state]->Render(nx, x, y);
		if (nx>0)
		{
			//RenderBoundingBox(190 - WHIP_BBOX_WIDTH + x, y + 15);
		}
		else
		{
			//RenderBoundingBox(x + 50,y+15);
		}
		
	}
	
//	RenderBoundingBox();
}

void CWhip::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{


	top = y + 15;	
	bottom = top + WHIP_BBOX_HEIGHT;
	if (nx < 0)
	{
		left = x + 50;
		right = left + WHIP_BBOX_WIDTH;
	}
	else if (nx > 0)
	{
		left = 190 - WHIP_BBOX_WIDTH + x;
		right = left + WHIP_BBOX_WIDTH;
	}
	
	if (state==WHIP_STATE_RED)
	{
		if (nx < 0)
		{
			left = x+25;
			right = left + WHIP_RED_BBOX_WIDTH;
		}
		else if (nx > 0)
		{
			left = 190 - WHIP_RED_BBOX_WIDTH+30 + x;
			right = left + WHIP_RED_BBOX_WIDTH;
		}
	}


}
//phai them cwhip vao object neu k se k update dc coevent
//cách 2 dùng AABB
void CWhip::Update(DWORD dt, vector<LPGAMEOBJECT>* cobjects)
{
	//duyet het cac objects, neu la Ctourch thi
//dung AABB xet 2 cai bounding box co chong len nhau hay khong
// neu co thi co xay ra va cham
	for (int i = 0; i < cobjects->size(); i++)
	{
		
		LPGAMEOBJECT e = cobjects->at(i);
		if (dynamic_cast<CTorch *>(e))
		{
			CTorch * f = dynamic_cast<CTorch*> (e);
			
			if (CGameObject::isColliding(this, f)==true)
			{
					DebugOut(L"Co va cham \n");
					// thuc ra chi ngung render neu va cham chua remove han can toi uu
					//xong
					f->SetState(TORCH_STATE_DISAPPEAR);
					
			}
		}
		else if (dynamic_cast<CGhoul *>(e))
		{
			CGhoul * g = dynamic_cast<CGhoul*> (e);
			if (CGameObject::isColliding(this, g) == true)
			{
				DebugOut(L"Co va cham \n");
				// thuc ra chi ngung render neu va cham chua remove han can toi uu
				//xong
				g->isRemove = true;	
			}
		}
		else if (dynamic_cast<CPanther *>(e))
		{
			CPanther * p = dynamic_cast<CPanther*> (e);
			if (CGameObject::isColliding(this, p) == true)
			{
				DebugOut(L"Co va cham \n");
				// thuc ra chi ngung render neu va cham chua remove han can toi uu
				//xong
				p->SetState(PANTHER_STATE_DIE);
			}
		}

	}



}



void CWhip::LoadResource()
{
	CSprites * sprites = CSprites::GetInstance();
	CAnimations * animations = CAnimations::GetInstance();

	CTextures * textures = CTextures::GetInstance();
	textures->Add(ID_TEX_WHIP, L"Resource\\sprites\\Weapons\\Whip.png", D3DCOLOR_XRGB(255, 0, 255));
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
}

CWhip::CWhip()
{
#pragma region whip
	LoadResource();
	this->AddAnimation(WHIP_NOLMAL_ANI_ID); //Nomal Whip /0
	this->AddAnimation(WHIP_BLUE_ANI_ID); //blue whip /1
	this->AddAnimation(WHIP_RED_ANI_ID); //red 2
	
#pragma endregion 
}


CWhip::~CWhip()
{
}

#include "SceneManager.h"

CSceneManager * CSceneManager::__instance = NULL;

CSceneManager * CSceneManager::GetInstance()
{
	if (__instance == NULL) __instance = new CSceneManager();
	return __instance;
}

void CSceneManager::GameUpdate()
{
}

void CSceneManager::LoadResource()
{

	CItem *items = new CItem();
	items->LoadResource();

	CDagger *dagger = new CDagger();
	dagger->LoadResource();

	CBrick *brick = new CBrick();
	brick->LoadResource();

	CGhoul *ghoul = new CGhoul();
	ghoul->LoadResource();

	CTorch *torch = new CTorch();
	torch->LoadResource();


}

void CSceneManager::initScene()
{

	switch (currentScene)
	{
	case SCENE_STATE_FIRST:
	{
		CGlobal::GetInstance()->objects.clear();
		CSIMON *simon = CSIMON::GetInstance();
		simon->SetPosition(100, 250);
		CGlobal::GetInstance()->objects.push_back(simon);
		for (int i = 0; i < 1536 / 32 + 4; i++)
		{
			CBrick *brick = new CBrick();
			brick->AddAnimation(601);
			brick->SetPosition(0 + i*30.0f, 350);
			CGlobal::GetInstance()->objects.push_back(brick);
		}

		CTorch* Torch = new CTorch();
		Torch->SetPosition(0 + 450, 350 - 60);
		Torch->SetState(TORCH_STATE_BURNING);
		Torch->setItemState(ITEM_STATE_BHEART);
		CGlobal::GetInstance()->objects.push_back(Torch);

		Torch = new CTorch();
		Torch->SetPosition(750, 350 - 60);
		Torch->SetState(TORCH_STATE_BURNING);
		Torch->setItemState(ITEM_STATE_NWHIP);
		CGlobal::GetInstance()->objects.push_back(Torch);

		Torch = new CTorch();
		Torch->SetPosition(950, 350 - 60);
		Torch->SetState(TORCH_STATE_BURNING);
		Torch->setItemState(ITEM_STATE_NWHIP);
		CGlobal::GetInstance()->objects.push_back(Torch);

		Torch = new CTorch();;
		Torch->SetPosition(1200, 350 - 60);
		Torch->SetState(TORCH_STATE_BURNING);
		Torch->setItemState(ITEM_STATE_DANGER);
		CGlobal::GetInstance()->objects.push_back(Torch);

		break;
	}
	case SCENE_STATE_SECOND:
	{
		CGlobal::GetInstance()->objects.clear();
		CSIMON *simon = CSIMON::GetInstance();
		simon->SetPosition(100, 100);
		CGlobal::GetInstance()->objects.push_back(simon);
		for (int i = 0; i < 1536 / 32 + 4; i++)
		{
			CBrick *brick = new CBrick();
			brick->AddAnimation(601);
			brick->SetPosition(0 + i*30.0f, 350);
			CGlobal::GetInstance()->objects.push_back(brick);
		}

		//and Goombas 
		for (int i = 0; i < 4; i++)
		{
			CGhoul* goomba = new CGhoul();

			goomba->SetPosition(400 + i * 100, 350 - 30 * 2);
			goomba->SetState(GOOMBA_STATE_WALKING);
			CGlobal::GetInstance()->objects.push_back(goomba);
		}



		break;
	}
	case SCENE_STATE_THIRD:
	{
		break;
	}

	}



}

CSceneManager::CSceneManager()
{
	currentScene = SCENE_STATE_FIRST;
}


CSceneManager::~CSceneManager()
{
}

#include "SceneManager.h"
#include"Camera.h"
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
	CTextures * textures = CTextures::GetInstance();
	textures->Add(ID_TEX_BBOX, L"Resource\\sprites\\bbox.png", D3DCOLOR_XRGB(201, 191, 231));
	textures->Add(ID_BACKGROUND_LV1, L"data\\map\\tileset.BMP", D3DCOLOR_XRGB(255, 255, 255));
	textures->Add(ID_BACKGROUND_LV2, L"data\\map\\lv2.BMP", D3DCOLOR_XRGB(255, 255, 255));
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

void CSceneManager::LoadMap()
{
	switch (currentScene)
	{
	case SCENE_STATE_FIRST: 
	{
	
		CTextures * textures = CTextures::GetInstance();
		LPDIRECT3DTEXTURE9 texMap = textures->Get(ID_BACKGROUND_LV1); //tex Map
		tileG = new CTileMap();
		tileG->SetMSize(1536, 384);
		tileG->SetTileSetHeight(640, 128);
		tileG->LoadTile(MAP_MATRIXPATH_SCENE1, texMap);

		break;
	}
	case SCENE_STATE_SECOND:
	{
	
		CTextures * textures = CTextures::GetInstance();
		LPDIRECT3DTEXTURE9 texMap = textures->Get(ID_BACKGROUND_LV2); //tex Map
		tileG = new CTileMap();
		tileG->SetMSize(5632, 768);
		tileG->SetTileSetHeight(640, 192);
		tileG->LoadTile(MAP_MATRIXPATH_SCENE2, texMap);
		break;
	}
	}
}

void CSceneManager::RenderMap()
{
	tileG->DrawMap();
}

void CSceneManager::initScene()
{

	switch (currentScene)
	{
	case SCENE_STATE_FIRST:
	{
		LoadMap();
		CGlobal::GetInstance()->objects.clear();
		CSIMON *simon = CSIMON::GetInstance();
		simon->SetPosition(100, 250);
		CGlobal::GetInstance()->objects.push_back(simon);
		for (int i = 0; i < 1536 / 32 + 4; i++)
		{
			CBrick *brick = new CBrick();
			brick->SetPosition(0 + i*32.0f, 350);
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
		LoadMap();
		CGlobal::GetInstance()->objects.clear();
		CSIMON *simon = CSIMON::GetInstance();
		simon->SetPosition(100, 200);
		CGlobal::GetInstance()->objects.push_back(simon);
		for (int i = 0; i < 5000 / 32 + 4; i++)
		{
			CBrick *brick = new CBrick();
			brick->SetState(BRICK_STATE_MODERN);
			brick->SetPosition(0 + i*30.0f, 370);
			CGlobal::GetInstance()->objects.push_back(brick);
		}

		//and Goombas 
		for (int i = 0; i < 4; i++)
		{
			CGhoul* goomba = new CGhoul();

			goomba->SetPosition(400 + i * 100, 370-GOOMBA_BBOX_HEIGHT);
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

void CSceneManager::sceneUpdate()
{
	if (ReplaceScene==true)
	{
		CCamera::GetInstance()->ResetCam();
		currentScene = SCENE_STATE_SECOND;
		initScene();
		ReplaceScene = false;
	}
}

CSceneManager::CSceneManager()
{
	ReplaceScene = false;
	currentScene = SCENE_STATE_FIRST;
}


CSceneManager::~CSceneManager()
{
}

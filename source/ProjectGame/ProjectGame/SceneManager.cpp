#include "SceneManager.h"
#include"Dagger.h"
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
	textures->Add(ID_TEX_ITEM_DANGER, L"Resource\\sprites\\Items\\KNIFE.png", D3DCOLOR_XRGB(255, 0, 255));
	CItem *items = new CItem();
	items->LoadResource();
	CDagger *dagger = new CDagger();
	dagger->LoadResource();
}

CSceneManager::CSceneManager()
{
}


CSceneManager::~CSceneManager()
{
}

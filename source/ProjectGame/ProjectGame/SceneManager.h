#pragma once
#include"Item.h"
#include"Dagger.h"
#include"Global.h"
#include"Brick.h"
#include"Whip.h"
#include"Torch.h"
#include"ghoul.h"
#include"Simon.h"

#define SCENE_STATE_FIRST 100
#define SCENE_STATE_SECOND 200
#define SCENE_STATE_THIRD 300
#define MAP_PATH_SCENE1 1
//CGhoul *goomba;
class CSceneManager
{
	int currentScene;
	static CSceneManager * __instance;
public:
	static CSceneManager * GetInstance();
	 void GameUpdate();
	 void LoadResource();
	 void initScene();
	 int getScene() { return currentScene; }
	 void ReplaceScene();
	 void Render();
	/*virtual void Draw();
	virtual void LoadMap();
	void getScene();
	void setScene();
	
*/
	CSceneManager();
	~CSceneManager();
};


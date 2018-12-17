#pragma once
#include"Item.h"
#include"Dagger.h"
#include"Global.h"
#include"Brick.h"
#include"Whip.h"
#include"Torch.h"
#include"ghoul.h"
#include"Simon.h"
#include"TileMap.h"
#define SCENE_STATE_FIRST 100
#define SCENE_STATE_SECOND 200
#define SCENE_STATE_THIRD 300
#define TEST_SCENE        900
#define MAP_PATH_SCENE1 1
#define MAP_MATRIXPATH_SCENE1  "data\\map\\tileset.txt"
#define MAP_MATRIXPATH_SCENE2  "data\\map\\lv2.txt"
//CGhoul *goomba;
class CSceneManager
{
	int currentScene;
	static CSceneManager * __instance;
	CTileMap *tileG;
public:
	static CSceneManager * GetInstance();
	 void GameUpdate();
	 void LoadResource();
	 void LoadMap();
	 void RenderMap();
	 void initScene();
	 void sceneUpdate();
	 int getScene() { return currentScene; }
	 bool ReplaceScene;
	 void Render();
	/*virtual void Draw();
	virtual void LoadMap();
	void getScene();
	void setScene();
	
*/
	CSceneManager();
	~CSceneManager();
};


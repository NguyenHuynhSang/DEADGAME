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
#define SCENE_STATE_FOURTH 400
#define TEST_SCENE        900
#define MAP_PATH_SCENE1 1
#define MAP_MATRIXPATH_SCENE1  "data\\map\\lv1.txt"
#define MAP_MATRIXPATH_SCENE2  "data\\map\\lv1_scene1.txt"
#define MAP_MATRIXPATH_SCENE3  "data\\map\\lv1_scene2.txt"
//CGhoul *goomba;
class CSceneManager
{
	int currentScene;
	int gameState = 0;
	static CSceneManager * __instance;
	CTileMap *tileG;
	LPGAMEOBJECT * listEnermy; // lưu enermy vào danh sách riêng để reset
public:
	static CSceneManager * GetInstance();
	 void LoadResource();
	 void LoadMap();
	 void RenderMap();
	 void initScene();
	 int getState() { return gameState; };
	 void sceneUpdate();
	 int getScene() { return currentScene; }
	 bool ReplaceScene;
	 void Render();
	 void Update(DWORD dt);
	/*virtual void Draw();
	virtual void LoadMap();
	void getScene();
	void setScene();
	
*/
	CSceneManager();
	~CSceneManager();
};


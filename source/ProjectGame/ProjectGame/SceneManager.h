#pragma once
#include"Item.h"



#define SCENE_STATE_FIRST 100
#define SCENE_STATE_SECOND 200
#define SCENE_STATE_THIRD 300


#define MAP_PATH_SCENE1 1

class CSceneManager
{
	int currentScene;
	static CSceneManager * __instance;
public:
	static CSceneManager * GetInstance();
	 void GameUpdate();
	 void LoadResource();
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


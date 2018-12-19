#pragma once

class CGameUI
{
	static CGameUI * __instance;

	int _score;
	int _SimonHP ;
	int _bossHP;
	int _gameTime;
	int _currentWeapon;
	int _state;
	char * _UIinfor;
public:
	static CGameUI * GetInstance();
	void Update(int sHP,int bHP,int time,int state,int cweapon);
	void Render();
	void LoadResource();
	CGameUI();
	~CGameUI();
};


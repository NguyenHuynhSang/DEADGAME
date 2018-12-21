#pragma once
#include<string>
using namespace std;
class CGameUI
{
	static CGameUI * __instance;

	int _score;
	int _SimonHP ;
	int _bossHP;
	int _gameTime;
	int _currentWeapon;
	int _state;
	std::string  _UIinfor;
public:
	static CGameUI * GetInstance();
	void Update();
	void Render();
	void LoadResource();
	CGameUI();
	~CGameUI();
};


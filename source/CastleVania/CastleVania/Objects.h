#pragma once
#include <Windows.h>
#include <d3dx9.h>
#include <vector>

#include "Sprites.h"

class CObjects
{
	float x;
	float y;
	float vx;
	int currentState;
public:
	void SetPosition(float x, float y) { this->x = x, this->y = y; }
	void SetState(int state) { this->currentState = state; }
	void Update(DWORD dt);
	void Render();
	CObjects();
	~CObjects();
};


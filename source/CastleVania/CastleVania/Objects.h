#pragma once
#include <Windows.h>
#include <d3dx9.h>
#include <vector>
#include"Canimation.h"
#include "Sprites.h"
using namespace std;



class CObjects;
typedef CObjects * LPGAMEOBJECT;
#define ID_TEX_BBOX -100		// special texture to draw object bounding box

class CObjects
{
protected:
	float x;
	float y;
	float dx;	// dx = vx*dt
	float dy;	// dy = vy*dt

	float vx;
	float vy;
	int nx;
	DWORD dt;
	int state;
	int currentState;
//	static vector<LPANIMATION> animations;
public:
	void SetPosition(float x, float y) { this->x = x, this->y = y; }
	void SetSpeed(float vx, float vy) { this->vx = vx, this->vy = vy; }
	void GetPosition(float &x, float &y) { x = this->x; y = this->y; }
	void GetSpeed(float &vx, float &vy) { vx = this->vx; vy = this->vy; }
	int GetState() { return this->state; }

	void AddAnimation(int aniId);

	void RenderBoundingBox();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom) = 0;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render() = 0;
	virtual void SetState(int state) { this->state = state; }
	CObjects();
	~CObjects();
};

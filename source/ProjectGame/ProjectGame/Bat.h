#pragma once


///***************************************************
//*    A * ( sin ( B * ( x – C ) ) ) + D             *
//*   A = Amplitude (Tallness) of the wave.          *
//*   B = How many waves there are for each cycle.   *
//*   C = How far to shift the wave’s X position.    *
//*   D = How far to shift the wave’s Y position.    *
//****************************************************
#include"GameObject.h"

#define BAT_FLYING_SPEED_X 0.15f;
#define BAT_FLYING_SPEED_y 0.2f;			


#define BAT_BBOX_WIDTH 32
#define BAT_BBOX_HEIGHT 32

#define BAT_STATE_IDLE   0
#define BAT_STATE_FLY    100


#define BAT_ANI_IDLE     0
#define BAT_ANI_FLY      1

#define BAT_OY_HEIGHT   30 // độ cao sóng  wave’s Y

#define BAT_OY_ROW

class CBat:public CGameObject
{
	float batOy;
public:
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render();
	void setNx(float xx) { nx = xx; };
	void setBatoy(float oy) { batOy = oy; };
	bool isEnable = false;
	virtual void LoadResource();
	CBat();
	~CBat();
};


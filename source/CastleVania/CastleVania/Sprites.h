#pragma once
#include<d3d9.h>
#include<Windows.h>
#include<unordered_map>
// k co name space k dung dc undordered_map
using namespace std;
class Sprites
{
private:
	int id;		// id of sprite
	int left;
	int right;
	int top;
	int buttom;
	LPDIRECT3DTEXTURE9 texture;
public:
	Sprites(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex);
	// vị trí vẽ sprite
	void Draw(float x, float y,int almpa=255);
	Sprites();
	~Sprites();
};

typedef Sprites * LPSPRITE;

class CSprites
{
	static CSprites * __instance;
	unordered_map<int, LPSPRITE> _sprites;
public:
	void Add(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex);
	LPSPRITE Get(int id);

	static CSprites * GetInstance();
};



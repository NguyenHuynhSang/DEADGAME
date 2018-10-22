#include"Sprites.h"
#include"Game.h"
CSprites * CSprites::__instance = NULL;

Sprites::Sprites(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex)
{
	this->top = top;
	this->id = id;
	this->right = right;
	this->buttom = bottom;
	this->left = left;
	this->texture = tex;

}

void Sprites::Draw(float x, float y)
{

	graphics *graphic = graphics::GetInstance();
	graphic->drawSprite(x, y, texture, left, top, right, buttom);

}

Sprites::Sprites()
{
}


Sprites::~Sprites()
{
}

void CSprites::Add(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex)
{
	LPSPRITE s = new Sprites(id, left, top, right, bottom, tex);
	_sprites[id] = s;
}

LPSPRITE CSprites::Get(int id)
{
	return _sprites[id];
}

CSprites * CSprites::GetInstance()
{
	if (__instance == NULL) __instance = new CSprites();
	return __instance;
}

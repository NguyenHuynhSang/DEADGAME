/*
cách vẽ hình bitmap lên màn hình
khó hơn sufface nhưng mạnh hơn

*/

#include "Textures.h"
#include"graphics.h"
CTextures * CTextures::__Teinstance = NULL;

CTextures::CTextures()
{

}

void CTextures::Add(int id, LPCWSTR filePath, D3DCOLOR transparentColor)
{

	LPDIRECT3DTEXTURE9 texture;
	graphics *gra = graphics::GetInstance();
	gra->initsprite(texture, filePath, transparentColor);
	textures[id] = texture;
}

LPDIRECT3DTEXTURE9 CTextures::Get(unsigned int i)
{
	return textures[i];
}

CTextures * CTextures::GetInstance()
{
	if (__Teinstance == NULL) __Teinstance = new CTextures();
	return __Teinstance;
}


//CTextures::~CTextures()
//{
//}

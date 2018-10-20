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
	D3DXIMAGE_INFO info;
	HRESULT result = D3DXGetImageInfoFromFile(filePath, &info);
// thieu dieu kien kiem tra o day

	LPDIRECT3DDEVICE9 d3ddv=graphics::GetInstance()->getDevice();
	LPDIRECT3DTEXTURE9 texture;
	result = D3DXCreateTextureFromFileEx(
		d3ddv,								// Pointer to Direct3D device object
		filePath,							// Path to the image to load
		info.Width,							// Texture width
		info.Height,						// Texture height
		1,
		D3DUSAGE_DYNAMIC,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		transparentColor,
		&info,
		NULL,
		&texture);								// Created texture pointer
	if (result!=D3D_OK)
	{
		OutputDebugString(L"[ERROR] CreateTextureFromFile failed\n");
		return;
	}
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

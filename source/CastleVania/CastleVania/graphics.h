#pragma once
#ifndef _GRAPHICS_H
#define _GRAPHICS_H
#include<d3d9.h>
#include<d3dx9.h>
#include"define.h"

class graphics
{
private:
	LPDIRECT3D9 d3d=NULL;
	// dùng để tạo device
	LPDIRECT3DDEVICE9 d3ddv=NULL;
	LPDIRECT3DSURFACE9 backBuffer;
	LPDIRECT3DTEXTURE9 LoadTexture(char *filename,D3DCOLOR tran);
	static graphics *__instance;
//	HWND hwnd;
	// các biến về kích thước màn hình;
	bool isFullScene;
	int width;
	int height;

public:
	void InitDirect(HWND hwnd, int width, int height, bool isfull);
	void safeRelease();
	void ShowBackBuffer();
	static graphics *GetInstance();
	LPDIRECT3DDEVICE9  getDevice() { return d3ddv; };
	void Present();
	void Begin();
	void End();
	void Clear();
	
	graphics();
	~graphics();
};


#endif // !_GRAPHICS_H


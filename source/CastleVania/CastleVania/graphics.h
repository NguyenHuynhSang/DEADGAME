#pragma once
/*=================================================
* Xử lý liên quan đến các lệnh directx ở đây
===================================================*/
#ifndef _GRAPHICS_H
#define _GRAPHICS_H
#include<d3d9.h>
#include<d3dx9.h>
#include"define.h"

class graphics
{
private:
	LPDIRECT3D9 d3d = NULL;
	// dùng để tạo device
	LPDIRECT3DDEVICE9 d3ddc= NULL;
	LPDIRECT3DSURFACE9 backBuffer=NULL;
	// sprite handler quản lý, gọi hàm thao tác sprite
	LPD3DXSPRITE spriteHandler;
	// lưu trữ thông tin sprite
	D3DXIMAGE_INFO info;
	static graphics *__instance;
//	HWND hwnd;
	// các biến về kích thước màn hình bổ xung sau mặc định WIndow=true;
	// w/h=800/600
	bool isFullScene;
	int width;
	int height;

public:
	void InitDirect(HWND hwnd, int width, int height, bool isfull);
	void safeRelease();
	void ShowBackBuffer();
	static graphics *GetInstance();
	LPDIRECT3DTEXTURE9 tex;
	LPDIRECT3DDEVICE9  getDevice() { return d3ddc; };
	void render_frame(void);

	void Present();
	void Begin();
	void End();
	void Clear();

	//ví dụ về initsprite
	void initsprite(int id, LPCWSTR filePath, D3DCOLOR transparentColor);
	void drawSprite(float x, float y,LPDIRECT3DTEXTURE9 texture, int left, int right, int top, int button);
	graphics();
	~graphics();
};


#endif // !_GRAPHICS_H


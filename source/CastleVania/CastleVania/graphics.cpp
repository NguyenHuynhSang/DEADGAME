#include "graphics.h"
#include<d3d9.h>
#include<d3dx9.h>

void graphics::InitDirect(HWND hwnd, int width, int height, bool isfull)
{
	
	d3d = Direct3DCreate9(D3D_SDK_VERSION);
	if (!d3d)
	{
		MessageBox(hwnd, "Loi qua trinh cai Direct3d", "Loi",MB_OK);
		return ;
	}
	// khai báo d3d parameters,set zeromemory trước khi truyền
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dpp.BackBufferCount = 1;

	RECT r;
	GetClientRect(hwnd, &r);	// retrieve Window width & height 

	d3dpp.BackBufferHeight = r.bottom + 1;
	d3dpp.BackBufferWidth = r.right + 1;

	//create d3d device
	
	d3d->CreateDevice(
		D3DADAPTER_DEFAULT, //số adapter
		D3DDEVTYPE_HAL, // có 2 loại , 1 loại là để kiểm thử
		hwnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		&d3ddv
	);
	//clear backbuffer to black

		if (d3ddv==NULL)
		{
			MessageBox(hwnd, "error create d3d device", "Loi", MB_OK);
			return ;
		}
		
		MessageBox(hwnd, "Done", "Complete", MB_OK);
		return ;


}

void graphics::safeRelease()
{
	//dùng câu lệnh trong macro để xóa an toàn
	//ex:#define SAFE_RELEASE(ptr) { if(ptr) { (ptr)->Release(); (ptr)=NULL; } }
	SAFE_RELEASE(d3d);
	SAFE_DELETE(d3ddv);
}

void graphics::ShowBackBuffer()
{
		d3ddv->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
	// pointer to the back buffer
			d3ddv->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &backBuffer);
	// hien thi back buffer len screen
			d3ddv->Present(NULL, NULL, NULL, NULL);
}

graphics::graphics()
{
	d3d = NULL;
	d3ddv = NULL;
	backBuffer = NULL;
	isFullScene = false;
	this->width = Default_Window_Width;
	this->height = Default_Window_Height;
}


graphics::~graphics()
{
	safeRelease();
}

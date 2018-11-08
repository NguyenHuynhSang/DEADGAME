#include "graphics.h"
#include<d3d9.h>
#include<d3dx9.h>

//ví dụ :D
#define SPRITE_PATH L"mario.png"
graphics * graphics::__instance = NULL;

void graphics::InitDirect(HWND hwnd, int width, int height, bool isfull)
{

	
	d3d=Direct3DCreate9(D3D_SDK_VERSION);
	if (!d3d)
	{
		OutputDebugString(L"[ERROR] create d3d failed\n");
		return;
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
		&d3ddc
	);
	//clear backbuffer to black

		if (d3ddc==NULL)
		{
			OutputDebugString(L"[ERROR] create device false failed\n");
			return ;
		}
		
		OutputDebugString(L"[Complete] complete\n");
		return;
}

void graphics::safeRelease()
{
	//dùng câu lệnh trong macro để xóa an toàn
	//ex:#define SAFE_RELEASE(ptr) { if(ptr) { (ptr)->Release(); (ptr)=NULL; } }
	SAFE_RELEASE(d3d);
	SAFE_DELETE(d3ddc);
}

void graphics::ShowBackBuffer()
{
	// pointer to the back buffer
	d3ddc->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &backBuffer);	
}

graphics * graphics::GetInstance()
{
	if (__instance==NULL)
	{
		__instance = new graphics();
	}
	return __instance;
}
//ex rander a single scene
void graphics::render_frame()
{
	d3ddc->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 40, 100), 1.0f, 0);

	d3ddc->BeginScene();

	//drawSprite(20,20,tex,1,1,100,100);	// draw sprite

	d3ddc->EndScene();

	// displays the created frame on the screen
	// translate backbuffer to frontbuffer
	d3ddc->Present(NULL, NULL, NULL, NULL);
}

void graphics::Present()
{
	// hien thi back buffer len screen// front buffer
	d3ddc->Present(NULL, NULL, NULL, NULL);
}

void graphics::Begin()
{
	d3ddc->BeginScene();
}

void graphics::End()
{
	d3ddc->EndScene();
}

void graphics::Clear()
{
	//D3DCOLOR_XRGB(0, 0, 0) black
	d3ddc->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 40, 100), 1.0f, 0);
}

void graphics::initsprite(LPDIRECT3DTEXTURE9 &tex, LPCWSTR filePath, D3DCOLOR transparentColor)
{
	// biến kiểm tra thành công
	HRESULT rs;
	// kết nối sprite handler với device và Direct3D
	rs=D3DXCreateSprite(d3ddc, &spriteHandler);
	if (rs!=D3D_OK)
	{
		OutputDebugString(L"[Error] Loi ket noi sprite handler voi device");
		return;
	}
	rs = D3DXGetImageInfoFromFile(filePath, &info);
	if (rs != D3D_OK)
	{
		OutputDebugString(L"[Error] Loi get imate from file");
		return;
	}
	rs = D3DXCreateTextureFromFileEx(
		d3ddc,                   // device liên kết với texture 
		filePath,		      // đường dẫn của sprite
		info.Width,			      // chiều dài của sprite
		info.Height,		      // chiều rộng của sprite
		1,
		D3DPOOL_DEFAULT,	      // kiểu surface
		D3DFMT_UNKNOWN,	          // định dạng surface
		D3DPOOL_DEFAULT,	      // lớp bộ nhớ cho texture
		D3DX_DEFAULT,		      // bộ lọc ảnh
		D3DX_DEFAULT,		      // bộ lọc mip
		transparentColor,   // chỉ ra màu trong suốt
		&info,			          // thông tin của sprite
		NULL,			          // đổ màu
		&tex			      // texture sẽ chứa sprite
	);
	if (rs != D3D_OK)
	{
		OutputDebugString(L"[Error] Loi create texture");
		return;
	}
	else
	{
		OutputDebugString(L"[Complete] Complete create texture");
	}
	// cẩn thận khúc này
	this->tex = tex;
}

void graphics::drawSprite(float x,float y, LPDIRECT3DTEXTURE9 texture, int left,int top, int right, int button)
{
	// khóa surface để sprite có thể vẽ 
	// D3DXSPRITE_ALPHABLEND hỗ trợ vẽ trong suốt nếu không thì để giá trị NULL
	spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

	// cài đặt vị trí cần hiển thị lên màn hình
	D3DXVECTOR3 position(x, y, 0);
	// chỉ hiển thị một phần
	RECT rt;
	rt.bottom = button;
	rt.left = left;
	rt.right = right;
	rt.top = top;
	spriteHandler->Draw(
		texture,				        // texture lưu sprite
		&rt,				            // diện tích cần hiển thị 
		NULL,				            // tâm dùng để vẽ, xoay
		&position,			            // vị trí sprite
		D3DCOLOR_XRGB(255, 255, 255)	// màu thay thế
	);

	// mở khóa surface để tiến trình khác sử dụng
	spriteHandler->End();
}

graphics::graphics()
{
	d3d = NULL;
	d3ddc = NULL;
	backBuffer = NULL;
	isFullScene = false;
	this->width = Default_Window_Width;
	this->height = Default_Window_Height;
}


graphics::~graphics()
{
	safeRelease();
}

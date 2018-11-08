////#include<d3d9.h>
////#include<d3dx9.h>
////#include<Windows.h>
#define Default_Window_Height 480
#define Default_Window_Width 640
#define APPNAME L"Casle Vania"
//static int SIMON_WALKING_TEST;
#define GAME_FPS 60



#define FULLSCREEN  0 // windowed or fullscreen

//macro dùng để thoát device khi thoát game
#define SAFE_RELEASE(ptr) { if(ptr) { (ptr)->Release(); (ptr)=NULL; } }
//macro xóa memory khi thoát game
#define SAFE_DELETE(ptr) { if (ptr) { delete (ptr); (ptr)=NULL; } }
//macro chữ hoa
#define SETCOLOR_ARGB(a,r,g,b)
// rút gọn tên thủ tục
//#define LP_3D LPDIRECT3D9


#define VK_SHIFT 0x10
#define VK_CONTROL 0x11
#define VK_ESCAPE 0x1B
#define VK_SPACE 0x20
#define VK_LEFT 0xCB // Arrow keys
#define VK_UP 0x26
#define VK_RIGHT 0x27
#define VK_DOWN 0x28





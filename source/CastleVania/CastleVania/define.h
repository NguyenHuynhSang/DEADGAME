////#include<d3d9.h>
////#include<d3dx9.h>
////#include<Windows.h>
#define Default_Window_Height 600
#define Default_Window_Width 800
#define APPNAME L"Casle Vania"

#define FULLSCREEN  0 // windowed or fullscreen

//macro dùng để thoát device khi thoát game
#define SAFE_RELEASE(ptr) { if(ptr) { (ptr)->Release(); (ptr)=NULL; } }
//macro xóa memory khi thoát game
#define SAFE_DELETE(ptr) { if (ptr) { delete (ptr); (ptr)=NULL; } }
//macro chữ hoa
#define SETCOLOR_ARGB(a,r,g,b)
// rút gọn tên thủ tục
//#define LP_3D LPDIRECT3D9




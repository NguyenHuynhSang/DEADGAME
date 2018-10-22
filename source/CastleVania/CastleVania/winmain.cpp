/*************************************************************
* WinMain chỉ dùng cho việc cài đặt cửa sổ game
* Mục đích tách code ra cho phần WinDown,Directx
*và game riêng biệt nhau
*
************************************************************/


#include"define.h"
#include<d3d9.h>
#include<d3dx9.h>
#include<Windows.h>
#include"graphics.h"
#include"Game.h"
LRESULT WINAPI WinProc(HWND, UINT, WPARAM, LPARAM);
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);
bool CreateMainWindow(HWND &,HINSTANCE,int);
// hàm setup windown properties
HINSTANCE hinst;
CGame *myGame;
	
//=======================================================================
// Starting point for a Windows application
//=======================================================================


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpCmdLine, int nCmdShow)
{
		
		MSG msg;
		HWND hwnd=NULL;
		if (!CreateMainWindow(hwnd, hInstance, nCmdShow))
			return 1;
		myGame = new CGame();
		myGame->Init(hwnd);
		try {
			// Create Graphics object
		//	graphic = new graphics;
			// Initialize Graphics, throws GameError
		//	graphic->InitDirect(hwnd, 800, 600, FULLSCREEN);
			// Main message loop
			
			int done = 0;
			while (!done)
			{
				// PeekMessage, a non-blocking method for checking for Windows
				// messages
				if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
				{
					// Look for quit message
					if (msg.message == WM_QUIT)
						done = 1;
					// Decode and pass messages on to WinProc
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
				myGame->render();
				//else
					//myGame->Draw();
			}
			// loi operator
			//SAFE_DELETE(graphic); // Free memory before exit
			return msg.wParam;
		}
		catch (...)
		{
			OutputDebugString(L"[ERROR]Unknowt\n");
		}
	//	SAFE_DELETE(graphic); // Free memory before exit
		return 0;
	}
bool CreateMainWindow(HWND &hwnd, HINSTANCE hInstance, int nCmdShow)
{
	WNDCLASSEX wcx;
	// Fill in the window class structure with parameters
	// that describe the main window.
	wcx.cbSize = sizeof(wcx); // Size of structure
	wcx.style = CS_HREDRAW | CS_VREDRAW;// Redraw if size changes
	wcx.lpfnWndProc = WinProc; // Points to window procedure
	wcx.cbClsExtra = 0; // No extra class memory
	wcx.cbWndExtra = 0; // No extra window memory
	wcx.hInstance = hInstance; // Handle to instance
	wcx.hIcon = NULL;
	wcx.hCursor = LoadCursor(NULL, IDC_ARROW); // Predefined arrow
											   // Black background
	wcx.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wcx.lpszMenuName = NULL; // Name of menu resource
	wcx.lpszClassName = APPNAME; // Name of window class
	wcx.hIconSm = NULL; // Small class icon
						// Register the window class
						// RegisterClassEx returns 0 on error
	if (RegisterClassEx(&wcx) == 0) // If error
		return false;
	// Set up the screen in windowed or fullscreen mode?
	DWORD style;
	if (FULLSCREEN)
		style = WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP;
	else
		style = WS_OVERLAPPEDWINDOW;
	// Create window
	hwnd = CreateWindow(
		APPNAME, // Name of the window class
		APPNAME, // Title bar text
		style, // Window style
		CW_USEDEFAULT, // Default horizontal position of window
		CW_USEDEFAULT, // Default vertical position of window
		Default_Window_Width, // Width of window
		Default_Window_Height, // Height of the window
		(HWND)NULL, // No parent window
		(HMENU)NULL, // No menu
		hInstance, // Handle to application instance
		(LPVOID)NULL); // No window parameters
					   // If there was an error creating the window
	if (!hwnd)
		return false;
	if (!FULLSCREEN) // If window
	{
		// Adjust window size so client area is GAME_WIDTH x GAME_HEIGHT
		RECT clientRect;
		GetClientRect(hwnd, &clientRect); // Get size of client area of
										  // window
		MoveWindow(hwnd,
			0, // Left
			0, // Top
			Default_Window_Width + (Default_Window_Width - clientRect.right), // Right
			Default_Window_Height + (Default_Window_Height - clientRect.bottom),// Bottom
			TRUE); // Repaint
				   // the window
	}
	// Show the window
	ShowWindow(hwnd, nCmdShow);
	// Send a WM_PAINT message to the window procedure
	UpdateWindow(hwnd);
	return true;
}


LRESULT WINAPI WinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		// Tell Windows to kill this program
		PostQuitMessage(0);
		return 0;
	
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}




#pragma once
///===============================================================================
//*Lớp xử lý các sự kiện bàn phím
//*
//*
//*
///===============================================================================
#ifndef _INPUT_
#define _INPUT_
#include<d3d9.h>
#include<d3dx9.h>
#include<dinput.h>
#include"debug.h"
//#define DIRECTINPUT_VERSION 0x0800
#define KEYBOARD_BUFFER_SIZE 1024
class CKeyEventHandler;
typedef CKeyEventHandler * LPKEYEVENTHANDLER;
class CInput
{
	static CInput * __instance;

	LPDIRECTINPUT8 di;// The DirectInput object   
	LPDIRECTINPUTDEVICE8 didv;		// The keyboard device 
	BYTE  keyStates[256];
	LPKEYEVENTHANDLER keyHandler;
	DIDEVICEOBJECTDATA keyEvents[KEYBOARD_BUFFER_SIZE];
public:
	static CInput * GetInstance();
	void InitKeyboard(HWND hWnd,LPKEYEVENTHANDLER handler);
	void ProcessKeyboard();
	int isKeyDown(int keyCode);
	CInput();
	~CInput();
};

#endif // !_INPUT_

class CKeyEventHandler
{
public:
	virtual void KeyState(BYTE *state) = 0;
	virtual void OnKeyDown(int KeyCode) = 0;
	virtual void OnKeyUp(int KeyCode) = 0;
};





#pragma once
/*====================================
ViewPort là một khung hình trong game và có 1 tọa độ trong thế giới game
World là tọa độ thực
==>Những đối tượng nằm trong ViewPort có thể thấy được
==>bài toán chuyển từ World sang ViewPort
để có thể nhìn thấy các đối tượng trong game
tọa độ thực tế trục y hướng lên trong game trục y hướng xuống
Flip theo trục Ox ==>y đảo ngược
========================================*/
#include<d3d9.h>
#include<d3dx9.h>
#include<Windows.h>
class CViewPort
{
	D3DXMATRIX mt;
	
public:
	//D3DXMatrixIdentity(&mt);
	CViewPort();
	~CViewPort();
};


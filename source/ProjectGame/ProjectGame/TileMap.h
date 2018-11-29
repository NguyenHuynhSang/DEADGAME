///=========================================================
// Chia map ra tile để tiết kiệm bộ nhớ khi vẽ map
// slip map ra tileset bằng tool
// tải lên ma trận tilemap và tileset sau đó dựa vào đó để vẽ map
//=========================================================
// chiều dài và rộng của mỗi tile

#pragma once
#include"debug.h"
#include"Sprites.h"

#include<fstream>


#define  TILE_WIDTH 32
#define  TILE_HEIGHT 32

class CTileMap
{

	// ham va cot tiles 
	int rows; 
	int cols;
	int **matrix; //ma tran tiles map
	// chiều dài và rộng của map
	float mapWidth;
	float mapHeight;


	float tileSetWidth;
	float tileSetHeight;

	

public:
	// load tile  tu file sau do luu vao ma tran
	void LoadTile(char *name, LPDIRECT3DTEXTURE9 tex);
	void DrawMap();
	void SetMSize(float mW, float mH) { mapWidth = mW; mapHeight = mH; };
	void SetTileSetHeight(float tsW, float tsH) { tileSetWidth = tsW; tileSetHeight = tsH; };
	void GetSize(float &mW, float &mH) { mW = this->mapWidth; mH = this->mapHeight; }
};

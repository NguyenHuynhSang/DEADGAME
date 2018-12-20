#include "TileMap.h"
#include"Camera.h"
#include"Global.h"
using namespace std;
void CTileMap::LoadTile(char * name, LPDIRECT3DTEXTURE9 tex)
{
		fstream f;
		f.open(name, ios::in);
		if (f.fail())
		{
			DebugOut(L"[LINE]%d,cant read file",__LINE__);
			return;

		}
		rows = mapHeight / TILE_HEIGHT;
		cols = mapWidth / TILE_WIDTH;
		//create a matrix
		matrix = new int*[rows];
		for (int i = 0; i < rows; i++)
		{
			matrix[i] = new int[cols];
		}

		int k1=0,j = 0;
		// cắt toàn bộ số trong text lưu vào mãng
		while (!f.eof())
		{
			int n;
			if (f>>n)
			{
				matrix[k1][j] = n;
				//DebugOut(L"M[%d][%d]=%d  \n", k1, j, n);
				j++;
				if (j>cols-1)
				{
					k1++;
					j = 0;
				}
			}
		}
		f.close();

//Duyệt ngược nên ra tào lau chỗ này mất mấy tiếng vò đầu bứt tóc
		int id = 1;		// id of tileset
		int tsRows = tileSetHeight / 32;
		int tsCols = tileSetWidth / 32;

		for (int i = 0; i < tsRows; i++)
		{
			for (int j = 0; j < tsCols; j++)
			{
				CSprites::GetInstance()->Add(id,j*TILE_HEIGHT,i*TILE_HEIGHT, j*TILE_HEIGHT + TILE_HEIGHT, i*TILE_HEIGHT + TILE_HEIGHT,tex);
				id++;
			}
		}



}
void CTileMap::DrawMap()
{
	// Dựa vào vị trí Cam để tìm ô đầu ô cuối trong Map, 
	//sau đó ta vẽ ra.
	float camX, camY;
	CCamera::GetInstance()->getCamera(camX, camY);
	// lấy ra cột đầu và cột cuối trong Viewport ;
	int beginCol =((int)camX)/32;
	//+1 vì nếu vẽ vừa đủ cột cuối cùng mỗi khi render sẽ nhấp nháy
	int endCol = ((int)camX + SCREEN_WIDTH) / 32+1;

	int beginRow=(int)camY / 32;
	for (int i = beginRow; i < rows; i++)
	{
		for (int j = beginCol; j < endCol; j++)
		{
			CSprites::GetInstance()->Get(matrix[i][j])->Draw(0,j*TILE_HEIGHT,i*TILE_HEIGHT+82);
		}
	}



}

#pragma once
///===============================================
//* Phân hoạch không gian để tiết kiệm bộ nhớ
//* giả sử có hàng nghìn object, nếu chúng ta render ,update, xét va chạm
//* tất cả các object đó, trong khi phần nhìn thấy (Viewport) nhỏ hơn
//* rất nhiều so với game world gây ra lãng phí và ảnh hưởng đến hiệu suất của game
//* Phân chia world game thành từng ô tạo thành grib
//* chỉ update , render và xét va chạm khi grib và viewport va chạm
//* ==> chỉ thêm vào object ở hàm main khi object nằm trong viewport
///================================================
#include <vector>
#include "Game.h"
#include "GameObject.h"

#define CELL_WIDTH 32
#define CELL_HEIGHT 32
class CCell
{
	float _width;
	float _height;
	vector<LPGAMEOBJECT> objects;
	public:
	void Update(DWORD dt);
	void Render();
	void addObject(LPGAMEOBJECT ob) { objects.push_back(ob); }
	vector<LPGAMEOBJECT> GetObjects() { return objects; }
	void DeleteObject(int pos) {objects.erase(objects.begin() + pos); }
	CCell();
	~CCell();
};
typedef CCell *LPCELL;

class Cells {
	LPCELL* cells;
	// cell row and col
	int _row;
	int _col;
public:
	void Init(LPGAMEOBJECT object);
	void Update(DWORD dt);
	void Render(float camX,float camY);
	//trả về list object nằm trong vùng grib va chạm với viewport
	void getListObject(vector<LPGAMEOBJECT> *objects);
	//void getIndex(float x,float y){x/CellWidth}
	CCell getCell(int row, int col) { return cells[row][col]; };
};


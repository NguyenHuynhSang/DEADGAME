#include "Cell.h"
#include"Camera.h"


void CCell::Update(DWORD dt)
{
	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->Update(dt);
	}
}

void CCell::Render()
{
	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->Render();
	}
}

CCell::CCell()		
{
	_width = CELL_WIDTH;
	_height = CELL_HEIGHT;
	objects.clear();


}


CCell::~CCell()
{
	
}

void Cells::Init(LPGAMEOBJECT object)
{
	// xét xem object đang thuộc cell nào
	int x = object->x / CELL_WIDTH;
	int y = object->y / CELL_HEIGHT;
	cells[x][y].addObject(object); // them vao list object
}

// chỉ update các object nằm trong cell chạm vào Viewport
void Cells::Update(DWORD dt)
{
	//lấy tọa độ góc trên bên trái ViewPort chia lấy
	//nguyên cho kích thước mỗi Node, ta nhận được cặp
	//số thứ tự của Cell đầu tiên chứa ViewPort, tạm gọi <xs, ys>
	
	//lấy tọa độ góc dưới  bên phải  ViewPort ==> <xe,ye>
	int xs, ys;
	int xe, ye;
	float camX, camY;
	CCamera::GetInstance()->getCamera(camX,camY);
	// cell đầu
	xs = (int)camX/CELL_WIDTH;
	ys = (int)camY / CELL_HEIGHT;
	//cell cuối
	xe = (int)CCamera::GetInstance()->getVPWidth()/ CELL_WIDTH;
	ye=(int)CCamera::GetInstance()->getVPHeight() / CELL_HEIGHT;

	for (int i = xs; i < xe; i++)
		for (int j = ys; j < ye; j++)
			cells[i][j].Update(dt);


}

void Cells::Render(float camX, float camY)
{
	int xs, ys;
	int xe, ye;
	CCamera::GetInstance()->getCamera(camX, camY);
	// cell đầu
	xs = (int)camX / CELL_WIDTH;
	ys = (int)camY / CELL_HEIGHT;// lưu ý phần thừa trên map
	//cell cuối
	xe = (int)CCamera::GetInstance()->getVPWidth() / CELL_WIDTH;
	ye = (int)CCamera::GetInstance()->getVPHeight() / CELL_HEIGHT;

	for (int i = xs; i < xe; i++)
		for (int j = ys; j < ye; j++)
			cells[i][j].Render();
}

void Cells::getListObject(vector<LPGAMEOBJECT>* objects)
{
	objects->clear();
	int xs, ys;
	int xe, ye;
	float camX, camY;
	CCamera::GetInstance()->getCamera(camX, camY);
	// cell đầu
	xs = (int)camX / CELL_WIDTH;
	ys = (int)camY / CELL_HEIGHT;// lưu ý phần thừa trên map
								 //cell cuối
	xe = (int)CCamera::GetInstance()->getVPWidth() / CELL_WIDTH;
	ye = (int)CCamera::GetInstance()->getVPHeight() / CELL_HEIGHT;
	for (int i = xs; i < xe; i++)
		for (int j = ys; j< ye; j++)
		{
			// cập nhật lại object và 
			LPGAMEOBJECT e = cells[i][j].GetObjects()[1];
			objects->push_back(e);
		}
			
}

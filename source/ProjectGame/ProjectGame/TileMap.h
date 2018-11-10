#pragma once


///=========================================================
// Chia map ra tile để tiết kiệm bộ nhớ khi vẽ map
// tải lên ma trận tile map sau đó dựa vào đó để vẽ map
class CTileMap
{


	int **matrix; //ma tran tiles map
	// số tiles 
	int rows; 
	int cols;

	// chiều dài và rộng của map
	float mapWidth;
	float mapHeight;
	// chiều dài và rộng của mỗi tile
	float tilesWidth;
	float tileHeight;



public:
	void Init();
	void LoadTile();
	void Draw();



	CTileMap();
	~CTileMap();
};


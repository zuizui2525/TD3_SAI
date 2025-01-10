#pragma once
#include "struct.h"

//行列
int const mapRow = 18;//行[y]
int const mapColumn = 21;//列[x]
//固定のサイズ
float const blockSize = 60.0f;

class Map {
public:
	//メンバ変数
	int map_[mapRow][mapColumn];
	Quad blocks_[mapRow][mapColumn];
	Images image_;
	//メンバ関数
	Map();
	~Map();
	void changeTheMap(int upload[mapRow][mapColumn]);
	void Update();
	void Draw();
};
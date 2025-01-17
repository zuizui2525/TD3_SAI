#include "map.h"
#include "Zuizui.h"

Map::Map() {
	for (int y = 0; y < mapRow; y++) {
		for (int x = 0; x < mapColumn; x++) {
			map_[y][x] = {};
			blocks_[y][x].size = blockSize;
			blocks_[y][x].radius = { blockSize / 2,blockSize / 2 };
			blocks_[y][x].pos = { blockSize * x + blocks_[y][x].radius.x,blockSize * y + blocks_[y][x].radius.y };
			blocks_[y][x].leftTop = {};
			blocks_[y][x].rightTop = {};
			blocks_[y][x].leftBottom = {};
			blocks_[y][x].rightBottom = {};
			blocks_[y][x].imagePos = { map_[y][x],0 };
			blocks_[y][x].imageWidth = 60;
			blocks_[y][x].imageHeight = 60;
			blocks_[y][x].image = image_.blocks;
			blocks_[y][x].color = WHITE;
		}
	}
}

Map::~Map() {

}

void Map::changeTheMap(int upload[mapRow][mapColumn]) {
	for (int y = 0; y < mapRow; y++) {
		for (int x = 0; x < mapColumn; x++) {
			map_[y][x] = upload[y][x];
		}
	}
}

void Map::Update() {
	for (int y = 0; y < mapRow; y++) {
		for (int x = 0; x < mapColumn; x++) {
			//マップの中身の変更
			blocks_[y][x].imagePos = { map_[y][x],0 };
			//四点の座標の更新
			blocks_[y][x].leftTop = { blocks_[y][x].pos.x - blocks_[y][x].radius.x,blocks_[y][x].pos.y - blocks_[y][x].radius.y };
			blocks_[y][x].rightTop = { blocks_[y][x].pos.x + blocks_[y][x].radius.x,blocks_[y][x].pos.y - blocks_[y][x].radius.y };
			blocks_[y][x].leftBottom = { blocks_[y][x].pos.x - blocks_[y][x].radius.x,blocks_[y][x].pos.y + blocks_[y][x].radius.y };
			blocks_[y][x].rightBottom = { blocks_[y][x].pos.x + blocks_[y][x].radius.x,blocks_[y][x].pos.y + blocks_[y][x].radius.y };
		}
	}
}

void Map::Draw() {
	for (int y = 0; y < mapRow; y++) {
		for (int x = 0; x < mapColumn; x++) {
			DrawQuad(blocks_[y][x]);
		}
	}
}

void Map::SetTile(int row, int column, int tileType) {
	if (row >= 0 && row < mapRow && column >= 0 && column < mapColumn) {
		map_[row][column] = tileType;  // 軌跡を指定位置に配置

		//blocks_[row][column].imagePos = { 2,0 }; //軌跡ブロックを表示
		blocks_[row][column].color = 0xffffff66; //仮の軌跡ブロック
	}
}

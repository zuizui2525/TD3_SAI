#include "Coin.h"

Coin::Coin() {
	for (int i = 0; i < kMaxCoinNum; i++) {
		coins_[i].size = blockSize;
		coins_[i].radius = { blockSize / 2,blockSize / 2 };
		coins_[i].pos = {};
		coins_[i].leftTop = {};
		coins_[i].rightTop = {};
		coins_[i].leftBottom = {};
		coins_[i].rightBottom = {};
		coins_[i].imagePos = {};
		coins_[i].imageWidth = 60;
		coins_[i].imageHeight = 60;
		coins_[i].image = image_.coin;
		coins_[i].color = WHITE;

		isTaken_[i] = false;
	}

	takeCount = 0;
}

Coin::~Coin() {}

void Coin::Spawn(Vector2<int> spawnPoint_[kMaxCoinNum]) {
	for (int i = 0; i < kMaxCoinNum; i++) {

		takeCount = 0;

		isTaken_[i] = false;

		// 配置座標を求める
		coins_[i].pos = 
		{ static_cast<float>(spawnPoint_[i].y * blockSize + coins_[i].radius.x),
		static_cast<float>(spawnPoint_[i].x * blockSize + coins_[i].radius.y) };

		// コインの4点を求める
		QuadCalculation(i);
	}
}

void Coin::Draw() {
	for (int i = 0; i < kMaxCoinNum; i++) {
		if (!isTaken_[i]) {
			DrawQuad(coins_[i]);
		}
	}
}

void Coin::QuadCalculation(int number)
{
	coins_[number].leftTop.x = coins_[number].pos.x - coins_[number].radius.x;
	coins_[number].leftTop.y = coins_[number].pos.y - coins_[number].radius.y;
	coins_[number].leftBottom.x = coins_[number].pos.x - coins_[number].radius.x;
	coins_[number].leftBottom.y = coins_[number].pos.y + coins_[number].radius.y;
	coins_[number].rightTop.x = coins_[number].pos.x + coins_[number].radius.x;
	coins_[number].rightTop.y = coins_[number].pos.y - coins_[number].radius.y;
	coins_[number].rightBottom.x = coins_[number].pos.x + coins_[number].radius.x;
	coins_[number].rightBottom.y = coins_[number].pos.y + coins_[number].radius.y;
}



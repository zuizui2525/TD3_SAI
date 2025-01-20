#include "Moo.h"

Moo::Moo(float x, float y) {
	enemy_.size = kSize;
	enemy_.radius = { kSize / 2.0f,kSize / 2.0f };
	enemy_.pos = { x * kSize + enemy_.radius.x,y * kSize + enemy_.radius.y };
	enemy_.leftTop = {};
	enemy_.rightTop = {};
	enemy_.leftBottom = {};
	enemy_.rightBottom = {};
	enemy_.imagePos = { 0,0 };
	enemy_.imageWidth = 60;
	enemy_.imageHeight = 60;
	enemy_.image = image_.enemy_mie;
	enemy_.color = WHITE;
	speed_ = kSpeed;
	isAlive_ = true;
	next_ = {};
	stop_ = {};
	advance_ = {};
	randNumber_ = {};
	moveCounter_ = 0;
	direction_ = UP;
}

Moo::~Moo() {
}

void Moo::Move(int map[mapRow][mapColumn]) {
	//AI部分①
	if (moveCounter_ >= kMoveCounter) {
		moveCounter_ = 0;
		//距離計算


	}

	//実際に動かす部分②
	switch (direction_) {
	case UP:
		//仮のposを進める
		next_.leftTop.x = static_cast<int>((enemy_.pos.x - enemy_.radius.x) / enemy_.size);
		next_.leftTop.y = static_cast<int>((enemy_.pos.y - enemy_.radius.y - speed_) / enemy_.size);
		next_.rightTop.x = static_cast<int>((enemy_.pos.x + enemy_.radius.x - 1.0f) / enemy_.size);
		next_.rightTop.y = static_cast<int>((enemy_.pos.y - enemy_.radius.y - speed_) / enemy_.size);
		//Blockがない時に進む
		if (map[next_.leftTop.y][next_.leftTop.x] != 0 && map[next_.rightTop.y][next_.rightTop.x] != 0) {
			enemy_.pos.y -= speed_;
			moveCounter_++;
		}
		//Novice::ScreenPrintf(0, 20, "UP");
		break;
	case DOWN:
		//仮のposを進める
		next_.leftBottom.x = static_cast<int>((enemy_.pos.x - enemy_.radius.x) / enemy_.size);
		next_.leftBottom.y = static_cast<int>((enemy_.pos.y + enemy_.radius.y - 1.0f + speed_) / enemy_.size);
		next_.rightBottom.x = static_cast<int>((enemy_.pos.x + enemy_.radius.x - 1.0f) / enemy_.size);
		next_.rightBottom.y = static_cast<int>((enemy_.pos.y + enemy_.radius.y - 1.0f + speed_) / enemy_.size);
		//Blockがない時に進む
		if (map[next_.leftBottom.y][next_.leftBottom.x] != 0 && map[next_.rightBottom.y][next_.rightBottom.x] != 0) {
			enemy_.pos.y += speed_;
			moveCounter_++;
		}
		//Novice::ScreenPrintf(0, 20, "DOWN");
		break;
	case LEFT:
		//仮のposを進める
		next_.leftTop.x = static_cast<int>((enemy_.pos.x - enemy_.radius.x - speed_) / enemy_.size);
		next_.leftTop.y = static_cast<int>((enemy_.pos.y - enemy_.radius.y) / enemy_.size);
		next_.leftBottom.x = static_cast<int>((enemy_.pos.x - enemy_.radius.x - speed_) / enemy_.size);
		next_.leftBottom.y = static_cast<int>((enemy_.pos.y + enemy_.radius.y - 1.0f) / enemy_.size);
		//Blockがない時に進む
		if (map[next_.leftTop.y][next_.leftTop.x] != 0 && map[next_.leftBottom.y][next_.leftBottom.x] != 0) {
			enemy_.pos.x -= speed_;
			moveCounter_++;
		}
		//Novice::ScreenPrintf(0, 20, "LEFT");
		break;
	case RIGHT:
		//仮のposを進める
		next_.rightTop.x = static_cast<int>((enemy_.pos.x + enemy_.radius.x - 1.0f + speed_) / enemy_.size);
		next_.rightTop.y = static_cast<int>((enemy_.pos.y - enemy_.radius.y) / enemy_.size);
		next_.rightBottom.x = static_cast<int>((enemy_.pos.x + enemy_.radius.x - 1.0f + speed_) / enemy_.size);
		next_.rightBottom.y = static_cast<int>((enemy_.pos.y + enemy_.radius.y - 1.0f) / enemy_.size);
		//Blockがない時に進む
		if (map[next_.rightTop.y][next_.rightTop.x] != 0 && map[next_.rightBottom.y][next_.rightBottom.x] != 0) {
			enemy_.pos.x += speed_;
			moveCounter_++;
		}
		//Novice::ScreenPrintf(0, 20, "RIGHT");
		break;
	}
	//Novice::ScreenPrintf(0, 0, "moveCounter = %d,randNumber = %d", moveCounter_, randNumber_);
}

void Moo::Update() {
	//四点の座標の更新
	enemy_.leftTop = { enemy_.pos.x - enemy_.radius.x,enemy_.pos.y - enemy_.radius.y };
	enemy_.rightTop = { enemy_.pos.x + enemy_.radius.x - 1.0f,enemy_.pos.y - enemy_.radius.y };
	enemy_.leftBottom = { enemy_.pos.x - enemy_.radius.x,enemy_.pos.y + enemy_.radius.y - 1.0f };
	enemy_.rightBottom = { enemy_.pos.x + enemy_.radius.x - 1.0f,enemy_.pos.y + enemy_.radius.y - 1.0f };
}

void Moo::Draw() {
	if (isAlive_) {
		DrawQuad(enemy_);
	}
}

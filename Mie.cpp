#include "Mie.h"

Mie::Mie(float x, float y) {
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
	enemy_.image = 0;
	enemy_.color = PURPLE;
	speed_ = kSpeed;
	isAlive_ = true;
	next_ = {};
	stop_ = {};
	advance_ = {};
	randNumber_ = {};
	moveCounter_ = 0;
	direction_ = UP;
}

Mie::~Mie() {
}

void Mie::Move(int map[mapRow][mapColumn]) {
	//AI部分①
	if (moveCounter_ >= kMoveCounter) {
		moveCounter_ = 0;
		prevDirection_ = direction_;

		//仮のposを進める
		//(stop_)
		stop_.leftTop.x = static_cast<int>((enemy_.pos.x - enemy_.radius.x) / enemy_.size);
		stop_.leftTop.y = static_cast<int>((enemy_.pos.y - enemy_.radius.y) / enemy_.size);
		stop_.rightTop.x = static_cast<int>((enemy_.pos.x + enemy_.radius.x - 1.0f) / enemy_.size);
		stop_.rightTop.y = static_cast<int>((enemy_.pos.y - enemy_.radius.y) / enemy_.size);
		stop_.leftBottom.x = static_cast<int>((enemy_.pos.x - enemy_.radius.x) / enemy_.size);
		stop_.leftBottom.y = static_cast<int>((enemy_.pos.y + enemy_.radius.y - 1.0f) / enemy_.size);
		stop_.rightBottom.x = static_cast<int>((enemy_.pos.x + enemy_.radius.x - 1.0f) / enemy_.size);
		stop_.rightBottom.y = static_cast<int>((enemy_.pos.y + enemy_.radius.y - 1.0f) / enemy_.size);
		//(advance_)
		advance_.leftTop.x = static_cast<int>((enemy_.pos.x - enemy_.radius.x - speed_) / enemy_.size);
		advance_.leftTop.y = static_cast<int>((enemy_.pos.y - enemy_.radius.y - speed_) / enemy_.size);
		advance_.rightTop.x = static_cast<int>((enemy_.pos.x + enemy_.radius.x - 1.0f + speed_) / enemy_.size);
		advance_.rightTop.y = static_cast<int>((enemy_.pos.y - enemy_.radius.y - speed_) / enemy_.size);
		advance_.leftBottom.x = static_cast<int>((enemy_.pos.x - enemy_.radius.x - speed_) / enemy_.size);
		advance_.leftBottom.y = static_cast<int>((enemy_.pos.y + enemy_.radius.y - 1.0f + speed_) / enemy_.size);
		advance_.rightBottom.x = static_cast<int>((enemy_.pos.x + enemy_.radius.x - 1.0f + speed_) / enemy_.size);
		advance_.rightBottom.y = static_cast<int>((enemy_.pos.y + enemy_.radius.y - 1.0f + speed_) / enemy_.size);

		if (map[advance_.leftTop.y][advance_.leftTop.x] == 0 && map[advance_.rightTop.y][stop_.rightTop.x] == 0 && map[stop_.leftBottom.y][advance_.leftBottom.x] == 0) {
			Novice::ScreenPrintf(0, 40, "UP,LEFT");
			randNumber_ = rand() % 2;
			switch (randNumber_) {
			case 0:
				direction_ = DOWN;
				break;
			case 1:
				direction_ = RIGHT;
				break;
			}
		} else if (map[advance_.leftTop.y][stop_.leftTop.x] == 0 && map[advance_.rightTop.y][advance_.rightTop.x] == 0 && map[stop_.rightBottom.y][advance_.rightBottom.x] == 0) {
			Novice::ScreenPrintf(0, 40, "UP,RIGHT");
			randNumber_ = rand() % 2;
			switch (randNumber_) {
			case 0:
				direction_ = DOWN;
				break;
			case 1:
				direction_ = LEFT;
				break;
			}
		} else if (map[stop_.leftTop.y][advance_.leftTop.x] == 0 && map[advance_.leftBottom.y][advance_.leftBottom.x] == 0 && map[advance_.rightBottom.y][stop_.rightBottom.x] == 0) {
			Novice::ScreenPrintf(0, 40, "DOWN,LEFT");
			randNumber_ = rand() % 2;
			switch (randNumber_) {
			case 0:
				direction_ = UP;
				break;
			case 1:
				direction_ = RIGHT;
				break;
			}
		} else if (map[stop_.rightTop.y][advance_.rightTop.x] == 0 && map[advance_.leftBottom.y][stop_.leftBottom.x] == 0 && map[advance_.rightBottom.y][advance_.rightBottom.x] == 0) {
			Novice::ScreenPrintf(0, 40, "DOWN,RIGHT");
			randNumber_ = rand() % 2;
			switch (randNumber_) {
			case 0:
				direction_ = UP;
				break;
			case 1:
				direction_ = LEFT;
				break;
			}
		} else if (map[advance_.leftTop.y][stop_.leftTop.x] == 0 && map[advance_.rightTop.y][stop_.rightTop.x] == 0 && map[advance_.leftBottom.y][stop_.leftBottom.x] == 0 && map[advance_.rightBottom.y][stop_.rightBottom.x] == 0) {
			Novice::ScreenPrintf(0, 40, "UP,DOWN,LEFT,RIGHT[Y,advance]");
			randNumber_ = rand() % 2;
			switch (randNumber_) {
			case 0:
				if (prevDirection_ != RIGHT) {
					direction_ = LEFT;
				}
				break;
			case 1:
				if (prevDirection_ != LEFT) {
					direction_ = RIGHT;
				}
				break;
			}
		} else if (map[stop_.leftTop.y][advance_.leftTop.x] == 0 && map[stop_.rightTop.y][advance_.rightTop.x] == 0 && map[stop_.leftBottom.y][advance_.leftBottom.x] == 0 && map[stop_.rightBottom.y][advance_.rightBottom.x] == 0) {
			Novice::ScreenPrintf(0, 40, "UP,DOWN,LEFT,RIGHT[X,advance]");
			randNumber_ = rand() % 2;
			switch (randNumber_) {
			case 0:
				if (prevDirection_ != DOWN) {
					direction_ = UP;
				}
				break;
			case 1:
				if (prevDirection_ != UP) {
					direction_ = DOWN;
				}
				break;
			}
		} else if (map[advance_.leftTop.y][stop_.leftTop.x] == 0 && map[advance_.rightTop.y][stop_.rightTop.x] == 0) {
			Novice::ScreenPrintf(0, 40, "UP");
			randNumber_ = rand() % 3;
			switch (randNumber_) {
			case 0:
				direction_ = DOWN;
				break;
			case 1:
				direction_ = LEFT;
				break;
			case 2:
				direction_ = RIGHT;
				break;
			}
		} else if (map[advance_.leftBottom.y][stop_.leftBottom.x] == 0 && map[advance_.rightBottom.y][stop_.rightBottom.x] == 0) {
			Novice::ScreenPrintf(0, 40, "DOWN");
			randNumber_ = rand() % 3;
			switch (randNumber_) {
			case 0:
				direction_ = UP;
				break;
			case 1:
				direction_ = LEFT;
				break;
			case 2:
				direction_ = RIGHT;
				break;
			}
		} else if (map[stop_.leftTop.y][advance_.leftTop.x] == 0 && map[stop_.leftBottom.y][advance_.leftBottom.x] == 0) {
			Novice::ScreenPrintf(0, 40, "LEFT");
			randNumber_ = rand() % 3;
			switch (randNumber_) {
			case 0:
				direction_ = UP;
				break;
			case 1:
				direction_ = DOWN;
				break;
			case 2:
				direction_ = RIGHT;
				break;
			}
		} else if (map[stop_.rightTop.y][advance_.rightTop.x] == 0 && map[stop_.rightBottom.y][advance_.rightBottom.x] == 0) {
			Novice::ScreenPrintf(0, 40, "RIGHT");
			randNumber_ = rand() % 3;
			switch (randNumber_) {
			case 0:
				direction_ = UP;
				break;
			case 1:
				direction_ = DOWN;
				break;
			case 2:
				direction_ = LEFT;
				break;
			}
		} else {
			Novice::ScreenPrintf(0, 40, "NONE");
			randNumber_ = rand() % 4;
			switch (randNumber_) {
			case 0:
				if (prevDirection_ != DOWN) {
					direction_ = UP;
				}
				break;
			case 1:
				if (prevDirection_ != UP) {
					direction_ = DOWN;
				}
				break;
			case 2:
				if (prevDirection_ != RIGHT) {
					direction_ = LEFT;
				}
				break;
			case 3:
				if (prevDirection_ != LEFT) {
					direction_ = RIGHT;
				}
				break;
			}
		}
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
		Novice::ScreenPrintf(0, 20, "UP");
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
		Novice::ScreenPrintf(0, 20, "DOWN");
		break;
	case LEFT:
		//仮のposを進める
		next_.leftTop.x = static_cast<int>((enemy_.pos.x - enemy_.radius.x - speed_) / enemy_.size);
		next_.leftTop.y = static_cast<int>((enemy_.pos.y - enemy_.radius.y ) / enemy_.size);
		next_.leftBottom.x = static_cast<int>((enemy_.pos.x - enemy_.radius.x - speed_) / enemy_.size);
		next_.leftBottom.y = static_cast<int>((enemy_.pos.y + enemy_.radius.y - 1.0f ) / enemy_.size);
		//Blockがない時に進む
		if (map[next_.leftTop.y][next_.leftTop.x] != 0 && map[next_.leftBottom.y][next_.leftBottom.x] != 0) {
			enemy_.pos.x -= speed_;
			moveCounter_++;
		}
		Novice::ScreenPrintf(0, 20, "LEFT");
		break;
	case RIGHT:
		//仮のposを進める
		next_.rightTop.x = static_cast<int>((enemy_.pos.x + enemy_.radius.x - 1.0f + speed_) / enemy_.size);
		next_.rightTop.y = static_cast<int>((enemy_.pos.y - enemy_.radius.y ) / enemy_.size);
		next_.rightBottom.x = static_cast<int>((enemy_.pos.x + enemy_.radius.x - 1.0f + speed_) / enemy_.size);
		next_.rightBottom.y = static_cast<int>((enemy_.pos.y + enemy_.radius.y - 1.0f ) / enemy_.size);
		//Blockがない時に進む
		if (map[next_.rightTop.y][next_.rightTop.x] != 0 && map[next_.rightBottom.y][next_.rightBottom.x] != 0) {
			enemy_.pos.x += speed_;
			moveCounter_++;
		}
		Novice::ScreenPrintf(0, 20, "RIGHT");
		break;
	}
	Novice::ScreenPrintf(0, 0, "moveCounter = %d,randNumber = %d", moveCounter_, randNumber_);
}

void Mie::Update() {
	//四点の座標の更新
	enemy_.leftTop = { enemy_.pos.x - enemy_.radius.x,enemy_.pos.y - enemy_.radius.y };
	enemy_.rightTop = { enemy_.pos.x + enemy_.radius.x - 1.0f,enemy_.pos.y - enemy_.radius.y };
	enemy_.leftBottom = { enemy_.pos.x - enemy_.radius.x,enemy_.pos.y + enemy_.radius.y - 1.0f };
	enemy_.rightBottom = { enemy_.pos.x + enemy_.radius.x - 1.0f,enemy_.pos.y + enemy_.radius.y - 1.0f };
}

void Mie::Draw() {
	if (isAlive_) {
		DrawQuad(enemy_);
	}
}

#include <math.h>
#include "Mar.h"

Mar::Mar() {
	enemy_.size = kSize;
	enemy_.radius = { kSize / 2.0f,kSize / 2.0f };
	enemy_.pos = { 0.0f,0.0f };
	enemy_.leftTop = {};
	enemy_.rightTop = {};
	enemy_.leftBottom = {};
	enemy_.rightBottom = {};
	enemy_.imagePos = { 0,0 };
	enemy_.imageWidth = 60;
	enemy_.imageHeight = 60;
	enemy_.image = image_.enemy_mar;
	enemy_.color = WHITE;
	speed_ = kSpeed;
	isAlive_ = false;
	next_ = {};
	stop_ = {};
	advance_ = {};
	randNumber_ = {};
	moveCounter_ = 0;
	direction_ = UP;
	lengthX_ = {};
	lengthY_ = {};
}

Mar::~Mar() {
	isAlive_ = false;
}

void Mar::Set(int x, int y, Direction direction) {
	enemy_.pos = { static_cast<float>(x) * kSize + enemy_.radius.x,static_cast<float>(y) * kSize + enemy_.radius.y };
	direction_ = direction;
	moveCounter_ = 0;
	isAlive_ = true;
}

void Mar::Move(int map[mapRow][mapColumn], Player* player) {
	if (isAlive_) {
		//AI部分①
		if (moveCounter_ >= kMoveCounter) {
			moveCounter_ = 0;
			prevDirection_ = direction_;

			//XとYの長さを求める
			lengthX_ = fabsf(player->quad_.pos.x - enemy_.pos.x);
			lengthY_ = fabsf(player->quad_.pos.y - enemy_.pos.y);

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

			if (//上以外の３方向が壁
				map[stop_.leftTop.y][advance_.leftTop.x] == 0//左上
				&& map[stop_.rightTop.y][advance_.rightTop.x] == 0//右上
				&& map[stop_.leftBottom.y][advance_.leftBottom.x] == 0//左下
				&& map[advance_.leftBottom.y][stop_.leftBottom.x] == 0//左下
				&& map[stop_.rightBottom.y][advance_.rightBottom.x] == 0//右下
				&& map[advance_.rightBottom.y][stop_.rightBottom.x] == 0//右下
				) {
				direction_ = UP;
			} else if (//下以外の３方向が壁
				map[stop_.leftTop.y][advance_.leftTop.x] == 0//左上
				&& map[advance_.leftTop.y][stop_.leftTop.x] == 0//左上
				&& map[stop_.rightTop.y][advance_.rightTop.x] == 0//右上
				&& map[advance_.rightTop.y][stop_.rightTop.x] == 0//右上
				&& map[stop_.leftBottom.y][advance_.leftBottom.x] == 0//左下
				&& map[stop_.rightBottom.y][advance_.rightBottom.x] == 0//右下
				) {
				direction_ = DOWN;
			} else if (//左以外の３方向が壁
				map[advance_.leftTop.y][stop_.leftTop.x] == 0//左上
				&& map[stop_.rightTop.y][advance_.rightTop.x] == 0//右上
				&& map[advance_.rightTop.y][stop_.rightTop.x] == 0//右上
				&& map[advance_.leftBottom.y][stop_.leftBottom.x] == 0//左下
				&& map[stop_.rightBottom.y][advance_.rightBottom.x] == 0//右下
				&& map[advance_.rightBottom.y][stop_.rightBottom.x] == 0//右下
				) {
				direction_ = LEFT;
			} else if (//右以外の３方向が壁
				map[stop_.leftTop.y][advance_.leftTop.x] == 0//左上
				&& map[advance_.leftTop.y][stop_.leftTop.x] == 0//左上
				&& map[advance_.rightTop.y][stop_.rightTop.x] == 0//右上
				&& map[stop_.leftBottom.y][advance_.leftBottom.x] == 0//左下
				&& map[advance_.leftBottom.y][stop_.leftBottom.x] == 0//左下
				&& map[advance_.rightBottom.y][stop_.rightBottom.x] == 0//右下
				) {
				direction_ = RIGHT;
			} else if (//左と上の２方向が壁
				map[stop_.leftTop.y][advance_.leftTop.x] == 0//左上
				&& map[advance_.leftTop.y][stop_.leftTop.x] == 0//左上
				&& map[advance_.rightTop.y][stop_.rightTop.x] == 0//右上
				&& map[stop_.leftBottom.y][advance_.leftBottom.x] == 0//左下
				) {
				if (player->quad_.pos.x >= enemy_.pos.x) {
					direction_ = RIGHT;
				} else {
					direction_ = DOWN;
				}
			} else if (//右と上の２方向が壁
				map[advance_.leftTop.y][stop_.leftTop.x] == 0//左上
				&& map[stop_.rightTop.y][advance_.rightTop.x] == 0//右上
				&& map[advance_.rightTop.y][stop_.rightTop.x] == 0//右上
				&& map[stop_.rightBottom.y][advance_.rightBottom.x] == 0//左下
				) {
				if (player->quad_.pos.x <= enemy_.pos.x) {
					direction_ = LEFT;
				} else {
					direction_ = DOWN;
				}
			} else if (//左と下の２方向が壁
				map[stop_.leftTop.y][advance_.leftTop.x] == 0//左上
				&& map[stop_.leftBottom.y][advance_.leftBottom.x] == 0//左下
				&& map[advance_.leftBottom.y][stop_.leftBottom.x] == 0//左下
				&& map[advance_.rightBottom.y][stop_.rightBottom.x] == 0//右下
				) {
				if (player->quad_.pos.x >= enemy_.pos.x) {
					direction_ = RIGHT;
				} else {
					direction_ = UP;
				}
			} else if (//右と下の２方向が壁
				map[stop_.rightTop.y][advance_.rightTop.x] == 0//右上
				&& map[advance_.leftBottom.y][stop_.leftBottom.x] == 0//左下
				&& map[stop_.rightBottom.y][advance_.rightBottom.x] == 0//右下
				&& map[advance_.rightBottom.y][stop_.rightBottom.x] == 0//右下
				) {
				if (player->quad_.pos.x <= enemy_.pos.x) {
					direction_ = LEFT;
				} else {
					direction_ = UP;
				}
			} else if (//上と下の２方向が壁
				map[advance_.leftTop.y][stop_.leftTop.x] == 0//左上
				&& map[advance_.rightTop.y][stop_.rightTop.x] == 0//右上
				&& map[advance_.leftBottom.y][stop_.leftBottom.x] == 0//左下
				&& map[advance_.rightBottom.y][stop_.rightBottom.x] == 0//右下
				) {
				if (player->quad_.pos.x >= enemy_.pos.x && prevDirection_ != LEFT) {
					direction_ = RIGHT;
				} else if (player->quad_.pos.x < enemy_.pos.x && prevDirection_ != RIGHT) {
					direction_ = LEFT;
				}
			} else if (//右と左の２方向が壁
				map[stop_.leftTop.y][advance_.leftTop.x] == 0//左上
				&& map[stop_.rightTop.y][advance_.rightTop.x] == 0//右上
				&& map[stop_.leftBottom.y][advance_.leftBottom.x] == 0//左下
				&& map[stop_.rightBottom.y][advance_.rightBottom.x] == 0//右下
				) {
				if (player->quad_.pos.y <= enemy_.pos.y && prevDirection_ != DOWN) {
					direction_ = UP;
				} else if (player->quad_.pos.y > enemy_.pos.y && prevDirection_ != UP) {
					direction_ = DOWN;
				}
			} else if (//上が壁
				map[advance_.leftTop.y][stop_.leftTop.x] == 0//左上
				&& map[advance_.rightTop.y][stop_.rightTop.x] == 0//右上
				) {
				if (player->quad_.pos.x >= enemy_.pos.x && prevDirection_ != LEFT) {
					direction_ = RIGHT;
				} else if (player->quad_.pos.x <= enemy_.pos.x && prevDirection_ != RIGHT) {
					direction_ = LEFT;
				} else if (prevDirection_ != UP) {
					direction_ = DOWN;
				}
			} else if (//下が壁
				map[advance_.leftBottom.y][stop_.leftBottom.x] == 0//左下
				&& map[advance_.rightBottom.y][stop_.rightBottom.x] == 0//右下
				) {
				if (player->quad_.pos.x >= enemy_.pos.x && prevDirection_ != LEFT) {
					direction_ = RIGHT;
				} else if (player->quad_.pos.x < enemy_.pos.x && prevDirection_ != RIGHT) {
					direction_ = LEFT;
				} else if (prevDirection_ != DOWN) {
					direction_ = UP;
				}
			} else if (//左が壁
				map[stop_.leftTop.y][advance_.leftTop.x] == 0//左上
				&& map[stop_.leftBottom.y][advance_.leftBottom.x] == 0//左下
				) {
				if (player->quad_.pos.y <= enemy_.pos.y && prevDirection_ != DOWN) {
					direction_ = UP;
				} else if (player->quad_.pos.y > enemy_.pos.y && prevDirection_ != UP) {
					direction_ = DOWN;
				} else if (prevDirection_ != LEFT) {
					direction_ = RIGHT;
				}
			} else if (//右が壁
				map[stop_.rightTop.y][advance_.rightTop.x] == 0//右上
				&& map[stop_.rightBottom.y][advance_.rightBottom.x] == 0//右下
				) {
				if (player->quad_.pos.y <= enemy_.pos.y && prevDirection_ != DOWN) {
					direction_ = UP;
				} else if (player->quad_.pos.y > enemy_.pos.y && prevDirection_ != UP) {
					direction_ = DOWN;
				} else if (prevDirection_ != RIGHT) {
					direction_ = LEFT;
				}
			} else {//全方向に壁がない
				if (lengthX_ >= lengthY_) {
					if (player->quad_.pos.x >= enemy_.pos.x && prevDirection_ != LEFT) {
						direction_ = RIGHT;
					} else if (player->quad_.pos.x < enemy_.pos.x && prevDirection_ != RIGHT) {
						direction_ = LEFT;
					}
				} else {
					if (player->quad_.pos.y <= enemy_.pos.y && prevDirection_ != DOWN) {
						direction_ = UP;
					} else if (player->quad_.pos.y > enemy_.pos.y && prevDirection_ != UP) {
						direction_ = DOWN;
					}
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
	}
}

void Mar::Update() {
	if (isAlive_) {
		//四点の座標の更新
		enemy_.leftTop = { enemy_.pos.x - enemy_.radius.x,enemy_.pos.y - enemy_.radius.y };
		enemy_.rightTop = { enemy_.pos.x + enemy_.radius.x,enemy_.pos.y - enemy_.radius.y };
		enemy_.leftBottom = { enemy_.pos.x - enemy_.radius.x,enemy_.pos.y + enemy_.radius.y };
		enemy_.rightBottom = { enemy_.pos.x + enemy_.radius.x,enemy_.pos.y + enemy_.radius.y };
	}
}

void Mar::Draw() {
	if (isAlive_) {
		DrawQuad(enemy_);
	}
}

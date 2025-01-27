#include <math.h>
#include "Mar.h"

Mar::Mar(float x, float y) {
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
	enemy_.image = image_.enemy_mar;
	enemy_.color = WHITE;
	speed_ = kSpeed;
	isAlive_ = true;
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
}

void Mar::Move(int map[mapRow][mapColumn], Player* player) {
	//AI�����@
	if (moveCounter_ >= kMoveCounter) {
		moveCounter_ = 0;
		prevDirection_ = direction_;

		//X��Y�̒�������߂�
		lengthX_ = fabsf(player->quad_.pos.x - enemy_.pos.x);
		lengthY_ = fabsf(player->quad_.pos.y - enemy_.pos.y);

		//����pos��i�߂�
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

		if (//��ȊO�̂R��������
			map[stop_.leftTop.y][advance_.leftTop.x] == 0//����
			&& map[stop_.rightTop.y][advance_.rightTop.x] == 0//�E��
			&& map[stop_.leftBottom.y][advance_.leftBottom.x] == 0//����
			&& map[advance_.leftBottom.y][stop_.leftBottom.x] == 0//����
			&& map[stop_.rightBottom.y][advance_.rightBottom.x] == 0//�E��
			&& map[advance_.rightBottom.y][stop_.rightBottom.x] == 0//�E��
			) {
			direction_ = UP;
		} else if (//���ȊO�̂R��������
			map[stop_.leftTop.y][advance_.leftTop.x] == 0//����
			&& map[advance_.leftTop.y][stop_.leftTop.x] == 0//����
			&& map[stop_.rightTop.y][advance_.rightTop.x] == 0//�E��
			&& map[advance_.rightTop.y][stop_.rightTop.x] == 0//�E��
			&& map[stop_.leftBottom.y][advance_.leftBottom.x] == 0//����
			&& map[stop_.rightBottom.y][advance_.rightBottom.x] == 0//�E��
			) {
			direction_ = DOWN;
		} else if (//���ȊO�̂R��������
			map[advance_.leftTop.y][stop_.leftTop.x] == 0//����
			&& map[stop_.rightTop.y][advance_.rightTop.x] == 0//�E��
			&& map[advance_.rightTop.y][stop_.rightTop.x] == 0//�E��
			&& map[advance_.leftBottom.y][stop_.leftBottom.x] == 0//����
			&& map[stop_.rightBottom.y][advance_.rightBottom.x] == 0//�E��
			&& map[advance_.rightBottom.y][stop_.rightBottom.x] == 0//�E��
			) {
			direction_ = LEFT;
		} else if (//�E�ȊO�̂R��������
			map[stop_.leftTop.y][advance_.leftTop.x] == 0//����
			&& map[advance_.leftTop.y][stop_.leftTop.x] == 0//����
			&& map[advance_.rightTop.y][stop_.rightTop.x] == 0//�E��
			&& map[stop_.leftBottom.y][advance_.leftBottom.x] == 0//����
			&& map[advance_.leftBottom.y][stop_.leftBottom.x] == 0//����
			&& map[advance_.rightBottom.y][stop_.rightBottom.x] == 0//�E��
			) {
			direction_ = RIGHT;
		} else if (//���Ə�̂Q��������
			map[stop_.leftTop.y][advance_.leftTop.x] == 0//����
			&& map[advance_.leftTop.y][stop_.leftTop.x] == 0//����
			&& map[advance_.rightTop.y][stop_.rightTop.x] == 0//�E��
			&& map[stop_.leftBottom.y][advance_.leftBottom.x] == 0//����
			) {
			if (player->quad_.pos.x >= enemy_.pos.x) {
				direction_ = RIGHT;
			} else {
				direction_ = DOWN;
			}
		} else if (//�E�Ə�̂Q��������
			map[advance_.leftTop.y][stop_.leftTop.x] == 0//����
			&& map[stop_.rightTop.y][advance_.rightTop.x] == 0//�E��
			&& map[advance_.rightTop.y][stop_.rightTop.x] == 0//�E��
			&& map[stop_.rightBottom.y][advance_.rightBottom.x] == 0//����
			) {
			if (player->quad_.pos.x <= enemy_.pos.x) {
				direction_ = LEFT;
			} else {
				direction_ = DOWN;
			}
		} else if (//���Ɖ��̂Q��������
			map[stop_.leftTop.y][advance_.leftTop.x] == 0//����
			&& map[stop_.leftBottom.y][advance_.leftBottom.x] == 0//����
			&& map[advance_.leftBottom.y][stop_.leftBottom.x] == 0//����
			&& map[advance_.rightBottom.y][stop_.rightBottom.x] == 0//�E��
			) {
			if (player->quad_.pos.x >= enemy_.pos.x) {
				direction_ = RIGHT;
			} else {
				direction_ = UP;
			}
		} else if (//�E�Ɖ��̂Q��������
			map[stop_.rightTop.y][advance_.rightTop.x] == 0//�E��
			&& map[advance_.leftBottom.y][stop_.leftBottom.x] == 0//����
			&& map[stop_.rightBottom.y][advance_.rightBottom.x] == 0//�E��
			&& map[advance_.rightBottom.y][stop_.rightBottom.x] == 0//�E��
			) {
			if (player->quad_.pos.x <= enemy_.pos.x) {
				direction_ = LEFT;
			} else {
				direction_ = UP;
			}
		} else if (//��Ɖ��̂Q��������
			map[advance_.leftTop.y][stop_.leftTop.x] == 0//����
			&& map[advance_.rightTop.y][stop_.rightTop.x] == 0//�E��
			&& map[advance_.leftBottom.y][stop_.leftBottom.x] == 0//����
			&& map[advance_.rightBottom.y][stop_.rightBottom.x] == 0//�E��
			) {
			if (player->quad_.pos.x >= enemy_.pos.x && prevDirection_ != LEFT) {
				direction_ = RIGHT;
			} else if (player->quad_.pos.x < enemy_.pos.x && prevDirection_ != RIGHT) {
				direction_ = LEFT;
			}
		} else if (//�E�ƍ��̂Q��������
			map[stop_.leftTop.y][advance_.leftTop.x] == 0//����
			&& map[stop_.rightTop.y][advance_.rightTop.x] == 0//�E��
			&& map[stop_.leftBottom.y][advance_.leftBottom.x] == 0//����
			&& map[stop_.rightBottom.y][advance_.rightBottom.x] == 0//�E��
			) {
			if (player->quad_.pos.y <= enemy_.pos.y && prevDirection_ != DOWN) {
				direction_ = UP;
			} else if (player->quad_.pos.y > enemy_.pos.y && prevDirection_ != UP) {
				direction_ = DOWN;
			}
		} else if (//�オ��
			map[advance_.leftTop.y][stop_.leftTop.x] == 0//����
			&& map[advance_.rightTop.y][stop_.rightTop.x] == 0//�E��
			) {
			if (player->quad_.pos.x >= enemy_.pos.x && prevDirection_ != LEFT) {
				direction_ = RIGHT;
			} else if (player->quad_.pos.x <= enemy_.pos.x && prevDirection_ != RIGHT) {
				direction_ = LEFT;
			} else if (prevDirection_ != UP) {
				direction_ = DOWN;
			}
		} else if (//������
			map[advance_.leftBottom.y][stop_.leftBottom.x] == 0//����
			&& map[advance_.rightBottom.y][stop_.rightBottom.x] == 0//�E��
			) {
			if (player->quad_.pos.x >= enemy_.pos.x && prevDirection_ != LEFT) {
				direction_ = RIGHT;
			} else if (player->quad_.pos.x < enemy_.pos.x && prevDirection_ != RIGHT) {
				direction_ = LEFT;
			} else if (prevDirection_ != DOWN) {
				direction_ = UP;
			}
		} else if (//������
			map[stop_.leftTop.y][advance_.leftTop.x] == 0//����
			&& map[stop_.leftBottom.y][advance_.leftBottom.x] == 0//����
			) {
			if (player->quad_.pos.y <= enemy_.pos.y && prevDirection_ != DOWN) {
				direction_ = UP;
			} else if (player->quad_.pos.y > enemy_.pos.y && prevDirection_ != UP) {
				direction_ = DOWN;
			} else if (prevDirection_ != LEFT) {
				direction_ = RIGHT;
			}
		} else if (//�E����
			map[stop_.rightTop.y][advance_.rightTop.x] == 0//�E��
			&& map[stop_.rightBottom.y][advance_.rightBottom.x] == 0//�E��
			) {
			if (player->quad_.pos.y <= enemy_.pos.y && prevDirection_ != DOWN) {
				direction_ = UP;
			} else if (player->quad_.pos.y > enemy_.pos.y && prevDirection_ != UP) {
				direction_ = DOWN;
			} else if (prevDirection_ != RIGHT) {
				direction_ = LEFT;
			}
		} else {//�S�����ɕǂ��Ȃ�
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

	//���ۂɓ����������A
	switch (direction_) {
	case UP:
		//����pos��i�߂�
		next_.leftTop.x = static_cast<int>((enemy_.pos.x - enemy_.radius.x) / enemy_.size);
		next_.leftTop.y = static_cast<int>((enemy_.pos.y - enemy_.radius.y - speed_) / enemy_.size);
		next_.rightTop.x = static_cast<int>((enemy_.pos.x + enemy_.radius.x - 1.0f) / enemy_.size);
		next_.rightTop.y = static_cast<int>((enemy_.pos.y - enemy_.radius.y - speed_) / enemy_.size);
		//Block���Ȃ����ɐi��
		if (map[next_.leftTop.y][next_.leftTop.x] != 0 && map[next_.rightTop.y][next_.rightTop.x] != 0) {
			enemy_.pos.y -= speed_;
			moveCounter_++;
		}
		//Novice::ScreenPrintf(0, 20, "UP");
		break;
	case DOWN:
		//����pos��i�߂�
		next_.leftBottom.x = static_cast<int>((enemy_.pos.x - enemy_.radius.x) / enemy_.size);
		next_.leftBottom.y = static_cast<int>((enemy_.pos.y + enemy_.radius.y - 1.0f + speed_) / enemy_.size);
		next_.rightBottom.x = static_cast<int>((enemy_.pos.x + enemy_.radius.x - 1.0f) / enemy_.size);
		next_.rightBottom.y = static_cast<int>((enemy_.pos.y + enemy_.radius.y - 1.0f + speed_) / enemy_.size);
		//Block���Ȃ����ɐi��
		if (map[next_.leftBottom.y][next_.leftBottom.x] != 0 && map[next_.rightBottom.y][next_.rightBottom.x] != 0) {
			enemy_.pos.y += speed_;
			moveCounter_++;
		}
		//Novice::ScreenPrintf(0, 20, "DOWN");
		break;
	case LEFT:
		//����pos��i�߂�
		next_.leftTop.x = static_cast<int>((enemy_.pos.x - enemy_.radius.x - speed_) / enemy_.size);
		next_.leftTop.y = static_cast<int>((enemy_.pos.y - enemy_.radius.y) / enemy_.size);
		next_.leftBottom.x = static_cast<int>((enemy_.pos.x - enemy_.radius.x - speed_) / enemy_.size);
		next_.leftBottom.y = static_cast<int>((enemy_.pos.y + enemy_.radius.y - 1.0f) / enemy_.size);
		//Block���Ȃ����ɐi��
		if (map[next_.leftTop.y][next_.leftTop.x] != 0 && map[next_.leftBottom.y][next_.leftBottom.x] != 0) {
			enemy_.pos.x -= speed_;
			moveCounter_++;
		}
		//Novice::ScreenPrintf(0, 20, "LEFT");
		break;
	case RIGHT:
		//����pos��i�߂�
		next_.rightTop.x = static_cast<int>((enemy_.pos.x + enemy_.radius.x - 1.0f + speed_) / enemy_.size);
		next_.rightTop.y = static_cast<int>((enemy_.pos.y - enemy_.radius.y) / enemy_.size);
		next_.rightBottom.x = static_cast<int>((enemy_.pos.x + enemy_.radius.x - 1.0f + speed_) / enemy_.size);
		next_.rightBottom.y = static_cast<int>((enemy_.pos.y + enemy_.radius.y - 1.0f) / enemy_.size);
		//Block���Ȃ����ɐi��
		if (map[next_.rightTop.y][next_.rightTop.x] != 0 && map[next_.rightBottom.y][next_.rightBottom.x] != 0) {
			enemy_.pos.x += speed_;
			moveCounter_++;
		}
		//Novice::ScreenPrintf(0, 20, "RIGHT");
		break;
	}
}

void Mar::Update() {
	//�l�_�̍��W�̍X�V
	enemy_.leftTop = { enemy_.pos.x - enemy_.radius.x,enemy_.pos.y - enemy_.radius.y };
	enemy_.rightTop = { enemy_.pos.x + enemy_.radius.x,enemy_.pos.y - enemy_.radius.y };
	enemy_.leftBottom = { enemy_.pos.x - enemy_.radius.x,enemy_.pos.y + enemy_.radius.y };
	enemy_.rightBottom = { enemy_.pos.x + enemy_.radius.x,enemy_.pos.y + enemy_.radius.y };
}

void Mar::Draw() {
	if (isAlive_) {
		DrawQuad(enemy_);
	}
}

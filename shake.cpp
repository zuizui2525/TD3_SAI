#include "shake.h"

Shake::Shake(int second,Size size) {
	isShake_ = false;
	timeSet_ = second * 60;
	second_ = second;
	timer_ = 0;
	randNumber_ = { 0,0 };
	size_ = size;
	randMax_ = 11;
	switch (size) {
	case SMALL:
		randMax_ = 11;
		break;
	case MEDIUM:
		randMax_ = 31;
		break;
	case LARGE:
		randMax_ = 61;
		break;
	}
	randMaxHalf_ = randMax_ / 2;

	startPoint_ = randMax_;
	endPoint_ = 0;
}

Shake::~Shake() {

}

void Shake::Update() {
	if (isShake_) {
		randMaxHalf_ = randMax_ / 2;
		if (timer_ < timeSet_) {
			//タイマーを進める
			timer_++;
			//ランダムな値を代入
			randNumber_.x = rand() % randMax_ - randMaxHalf_;
			randNumber_.y = rand() % randMax_ - randMaxHalf_;
			//最大値の減少
			switch (size_) {
			case SMALL:
				if (timer_ % (second_ * 6) == 0) {
					randMax_--;
				}
				break;
			case MEDIUM:
				if (timer_ % (second_ * 2) == 0) {
					randMax_--;
				}
				break;
			case LARGE:
				if (timer_ % second_ == 0) {
					randMax_--;
				}
				break;
			}
		} else {
			timeSet_ = second_ * 60;
			timer_ = 0;
			randNumber_ = { 0,0 };
			switch (size_) {
			case SMALL:
				randMax_ = 11;
				break;
			case MEDIUM:
				randMax_ = 31;
				break;
			case LARGE:
				randMax_ = 61;
				break;
			}
			isShake_ = false;
		}
	}
}
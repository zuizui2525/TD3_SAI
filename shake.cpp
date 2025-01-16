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
		if (0 < timer_) {
			// タイマーを進める
			timer_--;
			// ランダムな値を代入
			if (randMax_ != 0) {
				randNumber_.x = rand() % randMax_ - randMaxHalf_;
				randNumber_.y = rand() % randMax_ - randMaxHalf_;
			}
			// シェイクの範囲を割合で狭める
			randMax_ = (startPoint_ - endPoint_) * timer_ / (second_ * 60) + endPoint_;
			randMaxHalf_ = randMax_ / 2;
		} else {
			// タイマーが0になった時の処理
			timer_ = second_ * 60;
			randNumber_ = { 0,0 };
			randMaxHalf_ = randMax_ / 2;
			isShake_ = false;
		}
	}
	//Novice::ScreenPrintf(0, 0, "timer:%d", timer_);
}
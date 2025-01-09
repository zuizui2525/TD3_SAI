#pragma once
#include "struct.h"

class Shake {
private:
	//メンバ変数
	int timeSet_;
	int timer_;
	int second_;
	int randMax_;
	int randMaxHalf_;
	int startPoint_;
	int endPoint_;
	Size size_;
public:
	//メンバ変数
	Vector2<int> randNumber_;
	bool isShake_;
	//メンバ関数
	Shake(int second, Size size);
	~Shake();
	void Update();
};

#pragma once
#include <Novice.h>
#include "struct.h"
#include "Zuizui.h"
#include "map.h"

//固定のサイズ
float const kSize = 60.0f;
//固定のスピード
float const kSpeed = 6.0f;
//カウンターの限界
int const kMoveCounter = static_cast<int>(kSize / kSpeed);

class Enemy {
public:
	Quad enemy_;
	bool isAlive_;

protected:
	Images image_;
	Direction direction_;
	Direction prevDirection_;
	Vertices4<int> next_;
	Vertices4<int> stop_;
	Vertices4<int> advance_;
	
	float speed_;
	int randNumber_;
	int moveCounter_;
	
};


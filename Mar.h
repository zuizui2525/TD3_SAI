#pragma once
#include "Enemy.h"

class Mar :public Enemy {
public:
	float lengthX_;
	float lengthY_;
	Mar(float x, float y);
	~Mar();
	void Move(int map[mapRow][mapColumn], Player* player);
	void Update();
	void Draw();
};


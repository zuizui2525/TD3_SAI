#pragma once
#include "Enemy.h"

class Mar :public Enemy {
public:
	float lengthX_;
	float lengthY_;
	Mar();
	~Mar();
	void Set(int x, int y, Direction direction);
	void Move(int map[mapRow][mapColumn], Player* player);
	void Update();
	void Draw();
};


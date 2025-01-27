#pragma once
#include "Enemy.h"

class Moo: public Enemy {
public:
	float postionA_;
	float postionB_;
	float distance_;
	float reactionRange_;
	Moo();
	~Moo();
	void Set(int x, int y, Direction direction);
	void Move(int map[mapRow][mapColumn], Player* player);
	void Update();
	void Draw();
};


#pragma once
#include "Enemy.h"

class Moo: public Enemy {
public:
	float postionA_;
	float postionB_;
	float distance_;
	float reactionRange_;
	Moo(float x, float y);
	~Moo();
	void Move(int map[mapRow][mapColumn], Player* player);
	void Update();
	void Draw();
};


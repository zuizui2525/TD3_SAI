#pragma once
#include "Enemy.h"

class Moo: public Enemy {
public:
	Moo(float x, float y);
	~Moo();
	void Move(int map[mapRow][mapColumn]);
	void Update();
	void Draw();
};


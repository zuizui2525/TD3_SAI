#pragma once
#include "Enemy.h"

class Mie: public Enemy {
public:
	Mie(float x, float y);
	~Mie();
	void Move(int map[mapRow][mapColumn]);
	void Update();
	void Draw();
};


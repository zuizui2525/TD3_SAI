#pragma once
#include "Enemy.h"

class Mie: public Enemy {
public:
	Mie();
	~Mie();
	void Set(int x, int y, Direction direction);
	void Move(int map[mapRow][mapColumn]);
	void Update();
	void Draw();
};


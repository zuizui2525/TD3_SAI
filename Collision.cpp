#include <math.h>
#include "Collision.h"

int Collision(Quad* objA, Quad* objB, int modeSelect) {
	if (sqrtf(powf(objA->pos.x - objB->pos.x, 2.0f) + powf(objA->pos.y - objB->pos.y, 2.0f))
		< objA->radius.x + objB->radius.x) {
		if (modeSelect == 0) {
			return true;
		} else {
			return false;
		}
	} else {
		if (modeSelect == 0) {
			return false;
		} else {
			return true;
		}
	}
}

void CleanTlale(Enemy* enemy, Map* map) {
	if (map->map_[static_cast<int>(enemy->enemy_.pos.y / blockSize)][static_cast<int>(enemy->enemy_.pos.x / blockSize)] 
		== 2) {
		map->SetTile(static_cast<int>(enemy->enemy_.pos.y / blockSize), static_cast<int>(enemy->enemy_.pos.x / blockSize), 1);
	}
}

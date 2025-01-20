#include <math.h>
#include "Collision.h"

void Collision(Player* player, Enemy* enemy) {
	if (sqrtf(powf(player->playerQuad_.pos.x - enemy->enemy_.pos.x, 2.0f)	+ powf(player->playerQuad_.pos.y - enemy->enemy_.pos.y, 2.0f))
		<= player->playerQuad_.radius.x + enemy->enemy_.radius.x) {
		player->isAlive_ = false;
	}
}

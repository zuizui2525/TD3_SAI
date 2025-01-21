#pragma once
#include "Player.h"
#include "Enemy.h"
#include "map.h"

void Collision(Player* player, Enemy* enemy);

void CleanTlale(Enemy* enemy, Map* map);

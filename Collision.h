#pragma once
#include "Player.h"
#include "Enemy.h"
#include "map.h"

/// <summary>
/// 矩形Aと矩形Bの衝突判定
/// </summary>
/// <param name="objA">1つ目の矩形</param>
/// <param name="objB">2つ目の矩形</param>
/// <param name="modeSelect">衝突時に[0:true,1:false]のどっちをを返すか</param>
/// <returns></returns>
int Collision(Quad* objA, Quad* objB, int modeSelect);

/// <summary>
/// 敵が軌跡を道に戻す用の関数
/// </summary>
/// <param name="enemy">敵</param>
/// <param name="map">マップ情報</param>
void CleanTlale(Enemy* enemy, Map* map);

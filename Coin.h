#pragma once
#include <Novice.h>
#include "struct.h"
#include "Zuizui.h"
#include "map.h"

const int kMaxCoinNum = 5;

class Coin {
public:
	//メンバ変数
	Quad coins_[kMaxCoinNum];               // 座標

	int isTaken_[kMaxCoinNum];                            // プレイヤーに取られたかどうか

	int takeCount;

	Images image_;                          // 画像

	//メンバ関数
	Coin();
	~Coin();

	/// <summary>
	/// 
	/// </summary>
	/// <param name="spawnPoint_">コインの配置ポイント</param>
	void Spawn(Vector2<int> spawnPoint_[kMaxCoinNum]);

	/// <summary>
	/// コインの描画処理
	/// </summary>
	void Draw();

private:

	/// <summary>
	/// コインの4点の計算処理
	/// </summary>
	/// <param name="number">添字の指定</param>
	void QuadCalculation(int number);
};


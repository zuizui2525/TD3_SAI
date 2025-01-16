#pragma once
#include <Novice.h>
#include "struct.h"
#include "Zuizui.h"
#include "map.h"

class Player {
public: 
	// メンバ変数
	Images image_;                   //画像

	Quad playerQuad_{};              // 座標

	Vector2<int> leftTopMap_;        // マップ上の左上
	Vector2<int> leftBottomMap_;     // マップ上の左下
	Vector2<int> rightTopMap_;       // マップ上の右上
	Vector2<int> rightBottomMap_;    // マップ上の右下

	Vector2<int> nextLeftTopMap_;    // マップ上の左上
	Vector2<int> nextLeftBottomMap_; // マップ上の左下
	Vector2<int> nextRightTopMap_;   // マップ上の右上
	Vector2<int> nextRightBottomMap_;// マップ上の右下

	float speed_;                    // 速さ

private:
	
	int canMoveLeft_;                // 左に動けるかの判定(SE用)
	int canMoveRight_;               // 右に動けるかの判定(SE用)
	int canMoveUp_;                  // 上に動けるかの判定(SE用)
	int canMoveDown_;                // 下に動けるかの判定(SE用)

	int isPressLeft_;                // 左入力(SE用)
	int isPressRight_;               // 右入力(SE用)
	int isPressUp_;                  // 上入力(SE用)
	int isPressDown_;                // 下入力(SE用)

public:
	// メンバ関数

	/// <summary>
	/// コンストラクタ
	/// </summary>
	Player();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Player();

	/// <summary>
	/// 自機の操作処理
	/// </summary>
	/// <param name="keys">キー入力の取得</param>
	void Update(char* keys, int map[mapRow][mapColumn]);

	/// <summary>
	/// 自機の描画処理
	/// </summary>
	void Draw();

private:

	/// <summary>
	/// 自機の4点の計算処理
	/// </summary>
	void QuadCalculation();
};


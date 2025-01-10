#pragma once
#include <Novice.h>
#include "struct.h"
#include "Zuizui.h"

class Player {
private:
	// メンバ変数
	int canMoveLeft_;              // 左に動けるかの判定
	int canMoveRight_;             // 右に動けるかの判定
	int canMoveUp_;                // 上に動けるかの判定
	int canMoveDown_;              // 下に動けるかの判定

	int isPressLeft_ = false;       // 左入力
	int isPressRight_ = false;      // 右入力
	int isPressUp_ = false;         // 上入力
	int isPressDown_ = false;       // 下入力

public: 
	// メンバ変数
	Quad playerQuad_{};                // 座標
	Quad prevPlayerQuad_{};            // 座標の保存

	float speed_;                  // 速さ

    // メンバ関数

	/// <summary>
	/// コンストラクタ
	/// </summary>
	Player();

	/// <summary>
	/// デコンストラクタ
	/// </summary>
	~Player();

	/// <summary>
	/// 自機の操作処理
	/// </summary>
	/// <param name="keys">キー入力の取得</param>
	void Control(char* keys);

	/// <summary>
	/// 自機の衝突判定処理
	/// </summary>
	/// <param name="map">マップ情報の取得</param>
	void Collision(int map[18][21]);

	/// <summary>
	/// 自機の移動処理
	/// </summary>
	void Move();

	/// <summary>
	/// 自機の更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 自機の描画処理
	/// </summary>
	void Draw();
};


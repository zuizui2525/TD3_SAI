#pragma once
#include <Novice.h>
#include "struct.h"
#include "Zuizui.h"
#include "map.h"

class Player {
public: 
	// メンバ変数
	Images image_;                   //画像

	Quad quad_{};              // 座標

	Vertices4<int> mapCurrent_;      // マップ上の座標

	Vertices4<int> mapPrev_;         // 保存したマップ上の座標

	Vertices4<int> mapNext_;         // 次のマップ上の座標

	int isAlive_;                    // 生きているかのフラグ

private:

	Map& m_;                         // プレイヤーが移動するマップの参照

	float speed_;                    // 速さ

	Vector2<float> moveLength_;      // 移動量

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
	/// <param name="m">参照マップ(現在のマップ)</param>
	/// <param name="startX">初期地点X(マップ上の座標)</param>
	/// <param name="startY">初期地点Y(マップ上の座標)</param>
	Player(Map& m, int startX, int startY);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Player();

	/// <summary>
	/// プレイヤーの初期化
	/// </summary>
	/// <param name="startX">初期地点X(マップ上の座標)</param>
	/// <param name="startY">初期地点Y(マップ上の座標)</param>
	void Initialize(int startX, int startY);

	/// <summary>
	/// 自機の操作処理
	/// </summary>
	/// <param name="keys">キー入力の取得</param>
	void Update(char* keys);

	/// <summary>
	/// 自機の描画処理
	/// </summary>
	void Draw();

private:

	/// <summary>
	/// 自機の4点の計算処理
	/// </summary>
	void QuadCalculation();

	/// <summary>
	/// 通った後に軌跡ブロックを配置
	/// </summary>
	void LeaveTrail();
};


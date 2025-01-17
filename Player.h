#pragma once
#include <Novice.h>
#include "struct.h"
#include "Zuizui.h"
#include "map.h"

class Player {
public: 
	// メンバ変数
	Quad playerQuad_{};              // 座標	

	Vertices4<int> currentMap_;      // マップ上の座標

	Vertices4<int> prevMap_;         // 保存したマップ上の座標

	Vertices4<int> nextMap_;         // 次のマップ上の座標

private:

	Map& m_;                       // プレイヤーが移動するマップの参照

	float speed_;                    // 速さ

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
	Player(Map& m, int startX, int startY);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Player();

	/// <summary>
	/// 通った後に軌跡ブロックを配置
	/// </summary>
	void LeaveTrail();

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
};


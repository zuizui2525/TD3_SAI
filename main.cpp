#include <Novice.h>
#include "struct.h"
#include "Zuizui.h"
#include "map.h"
#include "mapCode.h"
#include "Player.h"

const char kWindowTitle[] = "ゲームタイトル";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	int const kWindowWidth = 1960;//windowの横幅
	int const kWindowHeight = 1080;//windowの縦幅
	Novice::Initialize(kWindowTitle, kWindowWidth, kWindowHeight);
	//フルスクリーン表示 ※これで少し重くなるっぽい
	//Novice::SetWindowMode(kFullscreen);

	Map* map = new Map();
	Player* player = new Player();

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///
		
		map->changeTheMap(map1);
		
		map->Update();

		// プレイヤーの処理

		//更新
		player->Update(keys, map->map_);
		
		///
		/// ↑更新処理ここまで
		///
		
		///
		/// ↓描画処理ここから
		///
		
		map->Draw();

		player->Draw();

		Novice::ScreenPrintf(1000, 20, "%d  %d", player->rightBottomMap_.y, player->rightBottomMap_.x);

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	delete player;
	delete map;

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}

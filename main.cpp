#include <Novice.h>
#include <time.h>
#include "struct.h"
#include "Zuizui.h"
#include "map.h"
#include "mapCode.h"
#include "Player.h"
#include "Enemy.h"
#include "Mie.h"
#include "Moo.h"

const char kWindowTitle[] = "ゲームタイトル";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	int const kWindowWidth = 1960;//windowの横幅
	int const kWindowHeight = 1080;//windowの縦幅
	Novice::Initialize(kWindowTitle, kWindowWidth, kWindowHeight);
	//フルスクリーン表示 ※これで少し重くなるっぽい
	Novice::SetWindowMode(kFullscreen);

	//確率(rand)
	unsigned int currentTime = unsigned(time(nullptr));//乱数
	srand(currentTime);

	Map* map = new Map();
	Player* player = new Player(*map, 1, 1);
	Mie* mie = new Mie(11,10);
	Mie* mie2 = new Mie(13, 10);

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
		
		if (keys[DIK_SPACE]) { // 軌跡反映用(仮)
			map->changeTheMap(map1);
		}
		map->Update();

		// プレイヤーの処理
		player->Update(keys);
		
		//敵の処理
		mie->Move(map->map_);
		mie->Update();
		mie2->Move(map->map_);
		mie2->Update();
		
		///
		/// ↑更新処理ここまで
		///
		
		///
		/// ↓描画処理ここから
		///
		
		map->Draw();

		player->Draw();

		mie->Draw();
		mie2->Draw();

		Novice::ScreenPrintf(1000, 0, "%d  %d", player->mapPrev_.leftTop.y, player->mapPrev_.leftTop.x);
		for (int y = 0; y < mapRow; y++) {
			for (int x = 0; x < mapColumn; x++) {
				Novice::ScreenPrintf(1300 + x * 20, y * 20, "%d", map->map_[y][x]);
			}
		}
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
	delete mie;
	delete mie2;

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}

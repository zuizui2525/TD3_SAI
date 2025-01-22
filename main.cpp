#include <Novice.h>
#include <time.h>
#include "struct.h"
#include "Zuizui.h"
#include "map.h"
#include "mapCode.h"
#include "Coin.h"
#include "Player.h"
#include "Enemy.h"
#include "Mie.h"
#include "Moo.h"
#include "Collision.h"

const char kWindowTitle[] = "ゲームタイトル";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	int const kWindowWidth = 1960;//windowの横幅
	int const kWindowHeight = 1080;//windowの縦幅
	Novice::Initialize(kWindowTitle, kWindowWidth, kWindowHeight);
	//フルスクリーン表示 ※これで少し重くなるっぽい
	//Novice::SetWindowMode(kFullscreen);

	//確率(rand)
	unsigned int currentTime = unsigned(time(nullptr));//乱数
	srand(currentTime);

	Map* map = new Map();
	Coin* coin = new Coin();
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

			coin->Spawn(coins1);

			coin->takeCount = 0;

			for (int i = 0; i < kMaxCoinNum; i++) {
				coin->isTaken_[i] = false;
			}

			player->Initialize(1, 1);
		}
		map->Update();

		// プレイヤーの処理
		player->Update(keys);
		
		//敵の処理
		mie->Move(map->map_);
		mie->Update();
		mie2->Move(map->map_);
		mie2->Update();
		
		// 衝突判定
		if (Collision(&player->playerQuad_, &mie->enemy_, 0)
			|| Collision(&player->playerQuad_, &mie2->enemy_, 0)) {
			player->isAlive_ = false;
		}

		for (int i = 0; i < kMaxCoinNum; i++) {
			if (!coin->isTaken_[i]) {
				if (Collision(&player->playerQuad_, &coin->coins_[i], 0)) {
					coin->isTaken_[i] = true;
					coin->takeCount++;
				}
			}
		}

		CleanTlale(mie, map);
		CleanTlale(mie2, map);

		///
		/// ↑更新処理ここまで
		///
		
		///
		/// ↓描画処理ここから
		///
		
		map->Draw();

		coin->Draw();

		player->Draw();

		mie->Draw();
		mie2->Draw();

		for (int y = 0; y < mapRow; y++) {
			for (int x = 0; x < mapColumn; x++) {
				Novice::ScreenPrintf(1300 + x * 20, y * 20, "%d", map->map_[y][x]);
			}
		}

		Novice::ScreenPrintf(1300, 1000, "SPACE: reset");

		Novice::ScreenPrintf(1300,800, "Coin: %d / %d", coin->takeCount, kMaxCoinNum);

		if (coin->takeCount >= kMaxCoinNum) {
			Novice::ScreenPrintf(1300, 700, "CLEAR");
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
	delete coin;
	delete mie;
	delete mie2;

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}

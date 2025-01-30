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
#include "Mar.h"
#include "Collision.h"

// ゲームのシーンの種類
enum SceneType {
	TITLE,
	STAGESELECT,
	GAME,
	GAMECLEAR,
	GAMEOVER
};

enum StageType {
	STAGE1,
	STAGE2,
	STAGE3
};


const char kWindowTitle[] = "1321_塞-SAI-";

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


	SceneType sceneType = TITLE;
	StageType stageType = STAGE1;

	int stageSelectNum = 1;
	int isGameStart = false;

	Map* map = new Map();
	Coin* coin = new Coin();
	Player* player = new Player(*map, 1, 1);
	Mie* mie = new Mie();//赤
	mie->Set(9, 10, UP);
	Moo* moo = new Moo();//青
	moo->Set(11, 10, UP);
	Mar* mar = new Mar();//紫
	mar->Set(13, 10, UP);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

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

		switch (sceneType)
		{
		case TITLE:

			if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) { // 軌跡反映用(仮)
				sceneType = STAGESELECT;
			}

			break;
		case STAGESELECT:

			if (keys[DIK_A] && !preKeys[DIK_A]
				|| keys[DIK_LEFT] && !preKeys[DIK_LEFT]) {
				stageSelectNum--;
			}

			if (keys[DIK_D] && !preKeys[DIK_D]
				|| keys[DIK_RIGHT] && !preKeys[DIK_RIGHT]) {
				stageSelectNum++;
			}

			if (stageSelectNum <= 0) {
				stageSelectNum = 3;
			}

			if (stageSelectNum > 3) {
				stageSelectNum = 1;
			}

			if (stageSelectNum == 1) {
				stageType = STAGE1;
			} else if (stageSelectNum == 2) {
				stageType = STAGE2;
			} else if (stageSelectNum == 3) {
				stageType = STAGE3;
			}


			if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) { // 軌跡反映用(仮)
				sceneType = GAME;
			}

			if (sceneType != STAGESELECT) { // 戻らなければ
				break;
			}

			switch (stageType)
			{
			case STAGE1:

				// 初期化
				mie->Set(5, 12, LEFT);
				moo->Set(15, 12, RIGHT);
				mar->Set(18, 5, LEFT);

				map->changeTheMap(map1);

				coin->Spawn(coins1);

				player->Initialize(5, 3);

				break;
			case STAGE2:

				// 初期化
				mie->Set(5, 6, DOWN);
				moo->Set(19, 10, LEFT);
				mar->Set(10, 16, UP);

				map->changeTheMap(map2);

				coin->Spawn(coins2);

				player->Initialize(10, 9);

				break;
			case STAGE3:

				// 初期化
				mie->Set(6, 6, RIGHT);
				moo->Set(16, 13, DOWN);
				mar->Set(4, 14, RIGHT);

				map->changeTheMap(map3);

				coin->Spawn(coins3);

				player->Initialize(10, 13);

				break;
			}

			break;
		case GAME:

			if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) { // 軌跡反映用(仮)
				isGameStart = true;
			}

			if (!isGameStart) {
				break;
			}

			switch (stageType)
			{
			case STAGE1:

				// リセット
				if (keys[DIK_R] && !preKeys[DIK_R]) { // 軌跡反映用(仮)
					mie->Set(5, 12, LEFT);
					moo->Set(15, 12, RIGHT);
					mar->Set(18, 5, LEFT);

					map->changeTheMap(map1);

					coin->Spawn(coins1);

					player->Initialize(5, 3);
				}

				break;
			case STAGE2:

				// リセット
				if (keys[DIK_R] && !preKeys[DIK_R]) { // 軌跡反映用(仮)
					mie->Set(5, 6, DOWN);
					moo->Set(19, 10, LEFT);
					mar->Set(10, 16, UP);

					map->changeTheMap(map2);

					coin->Spawn(coins2);

					player->Initialize(10, 9);
				}

				break;
			case STAGE3:

				// リセット
				if (keys[DIK_R] && !preKeys[DIK_R]) { // 軌跡反映用(仮)
					mie->Set(6, 6, RIGHT);
					moo->Set(16, 13, DOWN);
					mar->Set(4, 14, RIGHT);

					map->changeTheMap(map3);

					coin->Spawn(coins3);

					player->Initialize(10, 13);
				}

				break;
			}

			map->Update();

			// プレイヤーの処理
			player->Update(keys);

			//敵の処理
			mie->Move(map->map_);
			mie->Update();
			moo->Move(map->map_, player);
			moo->Update();
			mar->Move(map->map_, player);
			mar->Update();

			// 衝突判定
			if (Collision(&player->quad_, &mie->enemy_, 0)
				|| Collision(&player->quad_, &moo->enemy_, 0)
				|| Collision(&player->quad_, &mar->enemy_, 0)) {
				player->isAlive_ = false;
			}

			for (int i = 0; i < kMaxCoinNum; i++) {
				if (!coin->isTaken_[i]) {
					if (Collision(&player->quad_, &coin->coins_[i], 0)) {
						coin->isTaken_[i] = true;
						coin->takeCount++;
					}
				}
			}

			CleanTlale(mie, map);
			CleanTlale(moo, map);
			CleanTlale(mar, map);

			if (coin->takeCount >= kMaxCoinNum) {
				sceneType = GAMECLEAR;
			}

			if (!player->isAlive_) {
				sceneType = GAMEOVER;
			}

			break;
		case GAMECLEAR:

			if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) { // リセット
				sceneType = STAGESELECT;
				isGameStart = false;
			}

			if (sceneType != GAMECLEAR) { // 戻らなければ
				break;
			}

			switch (stageType)
			{
			case STAGE1:

				// 初期化
				mie->Set(5, 12, LEFT);
				moo->Set(15, 12, RIGHT);
				mar->Set(18, 5, LEFT);

				map->changeTheMap(map1);

				coin->Spawn(coins1);

				player->Initialize(5, 3);

				break;
			case STAGE2:

				// 初期化
				mie->Set(5, 6, DOWN);
				moo->Set(19, 10, LEFT);
				mar->Set(10, 16, UP);

				map->changeTheMap(map2);

				coin->Spawn(coins2);

				player->Initialize(10, 9);

				break;
			case STAGE3:

				// 初期化
				mie->Set(6, 6, RIGHT);
				moo->Set(16, 13, DOWN);
				mar->Set(4, 14, RIGHT);

				map->changeTheMap(map3);

				coin->Spawn(coins3);

				player->Initialize(10, 13);

				break;
			}

			break;
		case GAMEOVER:

			if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) { // リセット
				sceneType = STAGESELECT;
				isGameStart = false;
			}

			if (sceneType != GAMEOVER) { // 戻らなければ
				break;
			}

			switch (stageType)
			{
			case STAGE1:

				// 初期化
				mie->Set(5, 12, LEFT);
				moo->Set(15, 12, RIGHT);
				mar->Set(18, 5, LEFT);

				map->changeTheMap(map1);

				coin->Spawn(coins1);

				player->Initialize(5, 3);

				break;
			case STAGE2:

				// 初期化
				mie->Set(5, 6, DOWN);
				moo->Set(19, 10, LEFT);
				mar->Set(10, 16, UP);

				map->changeTheMap(map2);

				coin->Spawn(coins2);

				player->Initialize(10, 9);

				break;
			case STAGE3:

				// 初期化
				mie->Set(6, 6, RIGHT);
				moo->Set(16, 13, DOWN);
				mar->Set(4, 14, RIGHT);

				map->changeTheMap(map3);

				coin->Spawn(coins3);

				player->Initialize(10, 13);

				break;
			}

			break;
		}



		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		switch (sceneType)
		{
		case TITLE:

			Novice::ScreenPrintf(900, 540, "SAI");

			Novice::ScreenPrintf(840, 900, "Press to SPACE");

			break;
		case STAGESELECT:

			Novice::ScreenPrintf(900, 540, "STAGE %d", stageSelectNum);

			Novice::ScreenPrintf(840, 900, "WASD||Arrow : Stage Change");

			Novice::ScreenPrintf(840, 960, "SPACE : Select");
			break;
		case GAME:

			if (!isGameStart) {
				Novice::ScreenPrintf(900, 540, "SPACE : Start");
				break;
			}

			map->Draw();

			coin->Draw();

			player->Draw();

			mie->Draw();
			moo->Draw();
			mar->Draw();

			Novice::ScreenPrintf(1300, 1000, "R: reset");

			Novice::ScreenPrintf(1300, 800, "Coin: %d / %d", coin->takeCount, kMaxCoinNum);


			/*for (int y = 0; y < mapRow; y++) {
				for (int x = 0; x < mapColumn; x++) {
					Novice::ScreenPrintf(1300 + x * 20, y * 20, "%d", map->map_[y][x]);
				}
			}*/

			break;
		case GAMECLEAR:

			Novice::ScreenPrintf(900, 540, "CLEAR");

			Novice::ScreenPrintf(840, 960, "Press to SPACE");

			break;
		case GAMEOVER:

			Novice::ScreenPrintf(900, 540, "GAMEOVER");

			Novice::ScreenPrintf(840, 960, "Press to SPACE");

			break;
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
	delete moo;
	delete mar;

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}

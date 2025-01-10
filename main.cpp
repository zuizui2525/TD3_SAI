#include <Novice.h>
#include "struct.h"
#include "Zuizui.h"
#include "Player.h"

const char kWindowTitle[] = "ゲームタイトル";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	int const kWindowWidth = 1960;//windowの横幅
	int const kWindowHeight = 1080;//windowの縦幅
	Novice::Initialize(kWindowTitle, kWindowWidth, kWindowHeight);
	//フルスクリーン表示
	Novice::SetWindowMode(kFullscreen);

	//画像
	Images image;

	//マップ
	int const mapRow = 18;//行[y]
	int const mapColumn = 21;//列[x]
	int map[mapRow][mapColumn] = {
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},//1
		{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},//2
		{0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0},//3
		{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},//4
		{0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0},//5
		{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},//6
		{0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0},//7
		{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},//8
		{0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0},//9
		{0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0},//10
		{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},//11
		{0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0},//12
		{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},//13
		{0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0},//14
		{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},//15
		{0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0},//16
		{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},//17
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0} //18
	};
	//block
	float const blockSize = 60.0f;
	Quad blocks[mapRow][mapColumn];
	for (int y = 0; y < mapRow; y++) {
		for (int x = 0; x < mapColumn; x++) {
			blocks[y][x].size = blockSize;
			blocks[y][x].radius = { blockSize / 2,blockSize / 2 };
			blocks[y][x].pos = { blockSize * x + blocks[y][x].radius.x,blockSize * y + blocks[y][x].radius.y };
			blocks[y][x].leftTop = {};
			blocks[y][x].rightTop = {};
			blocks[y][x].leftBottom = {};
			blocks[y][x].rightBottom = {};
			blocks[y][x].imagePos = { map[y][x],0 };
			blocks[y][x].imageWidth = 60;
			blocks[y][x].imageHeight = 60;
			blocks[y][x].image = image.blocks;
			blocks[y][x].color = WHITE;
		}
	}

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
		
		for (int y = 0; y < mapRow; y++) {
			for (int x = 0; x < mapColumn; x++) {
				blocks[y][x].leftTop = { blocks[y][x].pos.x - blocks[y][x].radius.x,blocks[y][x].pos.y - blocks[y][x].radius.y };
				blocks[y][x].rightTop = { blocks[y][x].pos.x + blocks[y][x].radius.x,blocks[y][x].pos.y - blocks[y][x].radius.y };
				blocks[y][x].leftBottom = { blocks[y][x].pos.x - blocks[y][x].radius.x,blocks[y][x].pos.y + blocks[y][x].radius.y };
				blocks[y][x].rightBottom = { blocks[y][x].pos.x + blocks[y][x].radius.x,blocks[y][x].pos.y + blocks[y][x].radius.y };
			}
		}

		// プレイヤーの処理

		//操作
		player->Control(keys);
		//更新
		player->Update();
		//判定
		player->Collision(map);
		//移動
		player->Move();
		//更新
		player->Update();

		///
		/// ↑更新処理ここまで
		///
		
		///
		/// ↓描画処理ここから
		///
		
		for (int y = 0; y < mapRow; y++) {
			for (int x = 0; x < mapColumn; x++) {
				DrawQuad(blocks[y][x]);
			}
		}

		player->Draw();

		Novice::ScreenPrintf(1000, 0, "%f  %f", player->playerQuad_.leftTop.y / 60, player->playerQuad_.leftTop.x / 60);
		Novice::ScreenPrintf(1000, 20, "%f  %f", player->prevPlayerQuad_.leftTop.x, player->prevPlayerQuad_.leftTop.y);

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

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}

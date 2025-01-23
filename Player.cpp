#include <math.h>
#include "Player.h"

// public

Player::Player(Map& m, int startX, int startY) : m_(m) {
	// Quad
	playerQuad_.size = 1;
	playerQuad_.pos = { static_cast<float>(60 * startX + 30), static_cast<float>(60 * startY + 30) };
	playerQuad_.radius = { 30, 30 };
	playerQuad_.leftTop = { 0, 0 };
	playerQuad_.leftBottom = { 0, 0 };
	playerQuad_.rightTop = { 0, 0 };
	playerQuad_.rightBottom = { 0, 0 };
	playerQuad_.imagePos = { 0, 0 };
	playerQuad_.imageWidth = 60;
	playerQuad_.imageHeight = 60;
	playerQuad_.image = image_.player;
	playerQuad_.color = WHITE;

	// マップ上の番号
	mapCurrent_.leftTop = { startX, startY };
	mapCurrent_.leftBottom = { startX, startY };
	mapCurrent_.rightTop = { startX, startY };
	mapCurrent_.rightBottom = { startX, startY };

	mapPrev_ = mapCurrent_;

	mapNext_.leftTop = { 0, 0 };
	mapNext_.leftBottom = { 0, 0 };
	mapNext_.rightTop = { 0, 0 };
	mapNext_.rightBottom = { 0, 0 };

	// 生きているかのフラグ
	isAlive_ = true;

	// speed
	speed_ = 5;

	// 軌跡用
	moveLength_ = { 0, 0 };

	// フラグ
	canMoveLeft_ = false;
	canMoveRight_ = false;
	canMoveUp_ = false;
	canMoveDown_ = false;

	isPressLeft_ = false;
	isPressRight_ = false;
	isPressUp_ = false;
	isPressDown_ = false;
}

Player::~Player() {}

void Player::Initialize(int startX, int startY) {
	// 座標
	playerQuad_.pos = { static_cast<float>(60 * startX + 30), static_cast<float>(60 * startY + 30) };
	// マップ上の番号
	mapCurrent_.leftTop = { startX, startY };
	mapCurrent_.leftBottom = { startX, startY };
	mapCurrent_.rightTop = { startX, startY };
	mapCurrent_.rightBottom = { startX, startY };

	mapPrev_ = mapCurrent_;

	mapNext_.leftTop = { 0, 0 };
	mapNext_.leftBottom = { 0, 0 };
	mapNext_.rightTop = { 0, 0 };
	mapNext_.rightBottom = { 0, 0 };
	// 生きているかのフラグ
	isAlive_ = true;
	// 軌跡用
	moveLength_ = { 0, 0 };
}

void Player::Update(char* keys) {
	// 操作を初期化
	isPressLeft_ = false;
	isPressRight_ = false;
	isPressUp_ = false;
	isPressDown_ = false;

	//現在の4点
	QuadCalculation();

	//やられていたら更新しない
	if (!isAlive_) {
		return;
	}

	// プレイヤーを仮に進ませる
	if (keys[DIK_W] && !keys[DIK_S]) {
		//マップチップ上の座標
		mapNext_.leftTop.x = static_cast<int>((playerQuad_.pos.x - playerQuad_.radius.x) / blockSize);
		mapNext_.leftTop.y = static_cast<int>((playerQuad_.pos.y - playerQuad_.radius.y - speed_) / blockSize);
		mapNext_.rightTop.x = static_cast<int>((playerQuad_.pos.x + playerQuad_.radius.x - 1.0f) / blockSize);
		mapNext_.rightTop.y = static_cast<int>((playerQuad_.pos.y - playerQuad_.radius.y - speed_) / blockSize);

		//ブロックが無ければ進む
		if (m_.map_[mapNext_.leftTop.y][mapNext_.leftTop.x] == 1
			&& m_.map_[mapNext_.rightTop.y][mapNext_.rightTop.x] == 1) {
			playerQuad_.pos.y -= speed_;

			// 移動量の更新
			moveLength_.y -= speed_;

			canMoveUp_ = true; // SE用
		} else {
			canMoveUp_ = false;// SE用
		}

		isPressUp_ = true;     // SE用
	} 

	if (keys[DIK_S] && !keys[DIK_W]) {
		//マップチップ上の座標
		mapNext_.leftBottom.x = static_cast<int>((playerQuad_.pos.x - playerQuad_.radius.x) / blockSize);
		mapNext_.leftBottom.y = static_cast<int>((playerQuad_.pos.y + playerQuad_.radius.y - 1.0f + speed_) / blockSize);
		mapNext_.rightBottom.x = static_cast<int>((playerQuad_.pos.x + playerQuad_.radius.x - 1.0f) / blockSize);
		mapNext_.rightBottom.y = static_cast<int>((playerQuad_.pos.y + playerQuad_.radius.y - 1.0f + speed_) / blockSize);
		
		//ブロックが無ければ進む
		if (m_.map_[mapNext_.leftBottom.y][mapNext_.leftBottom.x] == 1
			&& m_.map_[mapNext_.rightBottom.y][mapNext_.rightBottom.x] == 1) {
			playerQuad_.pos.y += speed_;

			// 移動量の更新
			moveLength_.y += speed_;

			canMoveDown_ = true;
		} else {
			canMoveDown_ = false;
		}

		isPressDown_ = true;
	}

	if (keys[DIK_A] && !keys[DIK_D]) {
		//マップチップ上の座標
		mapNext_.leftTop.x = static_cast<int>((playerQuad_.pos.x - playerQuad_.radius.x - speed_) / blockSize);
		mapNext_.leftTop.y = static_cast<int>((playerQuad_.pos.y - playerQuad_.radius.y) / blockSize);
		mapNext_.leftBottom.x = static_cast<int>((playerQuad_.pos.x - playerQuad_.radius.x - speed_) / blockSize);
		mapNext_.leftBottom.y = static_cast<int>((playerQuad_.pos.y + playerQuad_.radius.y - 1.0f) / blockSize);

		//ブロックが無ければ進む
		if (m_.map_[mapNext_.leftTop.y][mapNext_.leftTop.x] == 1
			&& m_.map_[mapNext_.leftBottom.y][mapNext_.leftBottom.x] == 1) {
			playerQuad_.pos.x -= speed_;

			// 移動量の更新
			moveLength_.x -= speed_;

			canMoveLeft_ = true;
		} else {
			canMoveLeft_ = false;
		}

		isPressLeft_ = true; // SEとか用に
	} 
	
	if (keys[DIK_D] && !keys[DIK_A]) {
		//マップチップ上の座標
		mapNext_.rightTop.x = static_cast<int>((playerQuad_.pos.x + playerQuad_.radius.x - 1.0f + speed_) / blockSize);
		mapNext_.rightTop.y = static_cast<int>((playerQuad_.pos.y - playerQuad_.radius.y) / blockSize);
		mapNext_.rightBottom.x = static_cast<int>((playerQuad_.pos.x + playerQuad_.radius.x - 1.0f + speed_) / blockSize);
		mapNext_.rightBottom.y = static_cast<int>((playerQuad_.pos.y + playerQuad_.radius.y - 1.0f) / blockSize);
		
		//ブロックが無ければ進む
		if (m_.map_[mapNext_.rightTop.y][mapNext_.rightTop.x] == 1
			&& m_.map_[mapNext_.rightBottom.y][mapNext_.rightBottom.x] == 1) {
			playerQuad_.pos.x += speed_;
			
			// 移動量の更新
			moveLength_.x += speed_;

			canMoveRight_ = true;
		} else {
			canMoveRight_ = false;
		}

		isPressRight_ = true; // SEとか用に
	}

	// 範囲外の制限
	if (playerQuad_.pos.x <= playerQuad_.radius.x) {
		playerQuad_.pos.x = playerQuad_.radius.x;
	} else if (playerQuad_.pos.x >= mapColumn * blockSize - playerQuad_.radius.x) {
		playerQuad_.pos.x = mapColumn * blockSize - playerQuad_.radius.x;
	}
	if (playerQuad_.pos.y <= playerQuad_.radius.y) {
		playerQuad_.pos.y = playerQuad_.radius.y;
	} else if (playerQuad_.pos.y >= mapRow * blockSize - playerQuad_.radius.y) {
		playerQuad_.pos.y = mapRow * blockSize - playerQuad_.radius.y;
	}

	//現在の4点
	QuadCalculation();

	//プレイヤーが現在のマスから移動したら軌跡を残す
	LeaveTrail();
}

void Player::Draw() {
	if (isAlive_) {
		DrawQuad(playerQuad_);
	}
}

// private

void Player::QuadCalculation() {
	playerQuad_.leftTop.x = playerQuad_.pos.x - playerQuad_.radius.x;
	playerQuad_.leftTop.y = playerQuad_.pos.y - playerQuad_.radius.y;
	playerQuad_.leftBottom.x = playerQuad_.pos.x - playerQuad_.radius.x;
	playerQuad_.leftBottom.y = playerQuad_.pos.y + playerQuad_.radius.y;
	playerQuad_.rightTop.x = playerQuad_.pos.x + playerQuad_.radius.x;
	playerQuad_.rightTop.y = playerQuad_.pos.y - playerQuad_.radius.y;
	playerQuad_.rightBottom.x = playerQuad_.pos.x + playerQuad_.radius.x;
	playerQuad_.rightBottom.y = playerQuad_.pos.y + playerQuad_.radius.y;
}

void Player::LeaveTrail() {
	//プレイヤーが現在のマスから移動したら軌跡を残す
	if (fabs(moveLength_.x) >= blockSize || fabs(moveLength_.y) >= blockSize) {
		// xまたはyの移動量が60を超えた場合、軌跡を残す

		// 移動前の位置に軌跡を残す
		m_.SetTile(mapPrev_.leftTop.y, mapPrev_.leftTop.x, 2);  // プレイヤーが通った場所に軌跡を配置

		// x方向の移動
		if (fabs(moveLength_.x) >= blockSize) {
			int tileMoves = static_cast<int>(moveLength_.x / blockSize); // x方向の移動タイル数
			mapCurrent_.leftTop.x += tileMoves; // x座標を更新
			moveLength_.x -= tileMoves * blockSize; // 余剰分を残す
			// 移動後の位置を次回の移動前の位置として更新
			mapPrev_.leftTop.x = mapCurrent_.leftTop.x;
		}

		// y方向の移動
		if (fabs(moveLength_.y) >= blockSize) {
			int tileMoves = static_cast<int>(moveLength_.y / blockSize); // y方向の移動タイル数
			mapCurrent_.leftTop.y += tileMoves; // y座標を更新
			moveLength_.y -= tileMoves * blockSize; // 余剰分を残す
			// 移動後の位置を次回の移動前の位置として更新
			mapPrev_.leftTop.y = mapCurrent_.leftTop.y;
		}
	}
}
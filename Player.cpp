#include "Player.h"

// public

Player::Player() {
	// Quad
	playerQuad_.size = 1;
	playerQuad_.pos = { 90, 90 };
	playerQuad_.radius = { 30, 30 };
	playerQuad_.leftTop = { 0, 0 };
	playerQuad_.leftBottom = { 0, 0 };
	playerQuad_.rightTop = { 0, 0 };
	playerQuad_.rightBottom = { 0, 0 };
	playerQuad_.imagePos = { 0, 0 };
	playerQuad_.imageWidth = 60;
	playerQuad_.imageHeight = 60;
	playerQuad_.image = 0;
	playerQuad_.color = WHITE;

	// マップ上の番号
	leftTopMap_ = { 0, 0 };
	leftBottomMap_ = { 0, 0 };
	rightTopMap_ = { 0, 0 };
	rightBottomMap_ = { 0, 0 };

    nextLeftTopMap_ = { 0, 0 };
	nextLeftBottomMap_ = { 0, 0 };
	nextRightTopMap_ = { 0, 0 };
	nextRightBottomMap_ = { 0, 0 };

	// speed
	speed_ = 6;

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

void Player::Update(char* keys, int map[mapRow][mapColumn]) {
	// 操作を初期化
	isPressLeft_ = false;
	isPressRight_ = false;
	isPressUp_ = false;
	isPressDown_ = false;

	//現在の4点
	QuadCalculation();

	// プレイヤーを仮に進ませる
	if (keys[DIK_W] && !keys[DIK_S]) {
		//マップチップ上の座標
		nextLeftTopMap_.x = static_cast<int>((playerQuad_.pos.x - playerQuad_.radius.x) / blockSize);
		nextLeftTopMap_.y = static_cast<int>((playerQuad_.pos.y - playerQuad_.radius.y - speed_) / blockSize);
		nextRightTopMap_.x = static_cast<int>((playerQuad_.pos.x + playerQuad_.radius.x - 1.0f) / blockSize);
		nextRightTopMap_.y = static_cast<int>((playerQuad_.pos.y - playerQuad_.radius.y - speed_) / blockSize);

		//ブロックが無ければ進む
		if (map[nextLeftTopMap_.y][nextLeftTopMap_.x] == 1
			&& map[nextRightTopMap_.y][nextRightTopMap_.x] == 1) {
			playerQuad_.pos.y -= speed_;

			canMoveUp_ = true; // SE用
		} else {
			canMoveUp_ = false;// SE用
		}

		isPressUp_ = true;     // SE用
	} 

	if (keys[DIK_S] && !keys[DIK_W]) {
		//マップチップ上の座標
		nextLeftBottomMap_.x = static_cast<int>((playerQuad_.pos.x - playerQuad_.radius.x) / blockSize);
		nextLeftBottomMap_.y = static_cast<int>((playerQuad_.pos.y + playerQuad_.radius.y - 1.0f + speed_) / blockSize);
		nextRightBottomMap_.x = static_cast<int>((playerQuad_.pos.x + playerQuad_.radius.x - 1.0f) / blockSize);
		nextRightBottomMap_.y = static_cast<int>((playerQuad_.pos.y + playerQuad_.radius.y - 1.0f + speed_) / blockSize);
		
		//ブロックが無ければ進む
		if (map[nextLeftBottomMap_.y][nextLeftBottomMap_.x] == 1
			&& map[nextRightBottomMap_.y][nextRightBottomMap_.x] == 1) {
			playerQuad_.pos.y += speed_;

			canMoveDown_ = true;
		} else {
			canMoveDown_ = false;
		}

		isPressDown_ = true;
	}

	if (keys[DIK_A] && !keys[DIK_D]) {
		//マップチップ上の座標
		nextLeftTopMap_.x = static_cast<int>((playerQuad_.pos.x - playerQuad_.radius.x - speed_) / blockSize);
		nextLeftTopMap_.y = static_cast<int>((playerQuad_.pos.y - playerQuad_.radius.y) / blockSize);
		nextLeftBottomMap_.x = static_cast<int>((playerQuad_.pos.x - playerQuad_.radius.x - speed_) / blockSize);
		nextLeftBottomMap_.y = static_cast<int>((playerQuad_.pos.y + playerQuad_.radius.y - 1.0f) / blockSize);

		//ブロックが無ければ進む
		if (map[nextLeftTopMap_.y][nextLeftTopMap_.x] == 1
			&& map[nextLeftBottomMap_.y][nextLeftBottomMap_.x] == 1) {
			playerQuad_.pos.x -= speed_;

			canMoveLeft_ = true;
		} else {
			canMoveLeft_ = false;
		}

		isPressLeft_ = true; // SEとか用に
	} 
	
	if (keys[DIK_D] && !keys[DIK_A]) {
		//マップチップ上の座標
		nextRightTopMap_.x = static_cast<int>((playerQuad_.pos.x + playerQuad_.radius.x - 1.0f + speed_) / blockSize);
		nextRightTopMap_.y = static_cast<int>((playerQuad_.pos.y - playerQuad_.radius.y) / blockSize);
		nextRightBottomMap_.x = static_cast<int>((playerQuad_.pos.x + playerQuad_.radius.x - 1.0f + speed_) / blockSize);
		nextRightBottomMap_.y = static_cast<int>((playerQuad_.pos.y + playerQuad_.radius.y - 1.0f) / blockSize);
		
		//ブロックが無ければ進む
		if (map[nextRightTopMap_.y][nextRightTopMap_.x] == 1
			&& map[nextRightBottomMap_.y][nextRightBottomMap_.x] == 1) {
			playerQuad_.pos.x += speed_;

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
}

void Player::Draw() {
	DrawQuad(playerQuad_);
}

// private

void Player::QuadCalculation() {
	playerQuad_.leftTop.x = playerQuad_.pos.x - playerQuad_.radius.x;
	playerQuad_.leftTop.y = playerQuad_.pos.y - playerQuad_.radius.y;
	playerQuad_.leftBottom.x = playerQuad_.pos.x - playerQuad_.radius.x;
	playerQuad_.leftBottom.y = playerQuad_.pos.y + playerQuad_.radius.y - 1.0f;
	playerQuad_.rightTop.x = playerQuad_.pos.x + playerQuad_.radius.x - 1.0f;
	playerQuad_.rightTop.y = playerQuad_.pos.y - playerQuad_.radius.y;
	playerQuad_.rightBottom.x = playerQuad_.pos.x + playerQuad_.radius.x - 1.0f;
	playerQuad_.rightBottom.y = playerQuad_.pos.y + playerQuad_.radius.y - 1.0f;
}

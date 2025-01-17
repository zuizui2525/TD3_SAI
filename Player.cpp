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
	currentMap_.leftTop = { startX, startY };
	currentMap_.leftBottom = { startX, startY };
	currentMap_.rightTop = { startX, startY };
	currentMap_.rightBottom = { startX, startY };

	prevMap_.leftTop = currentMap_.leftTop;
	prevMap_.leftBottom = currentMap_.leftBottom;
	prevMap_.rightTop = currentMap_.rightTop;
	prevMap_.rightBottom = currentMap_.rightBottom;

	nextMap_.leftTop = { 0, 0 };
	nextMap_.leftBottom = { 0, 0 };
	nextMap_.rightTop = { 0, 0 };
	nextMap_.rightBottom = { 0, 0 };

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

void Player::LeaveTrail() {
	m_.SetTile(prevMap_.leftTop.y, prevMap_.leftTop.x, 2);  // プレイヤーが通った場所に軌跡を配置
}

void Player::Update(char* keys) {
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
		nextMap_.leftTop.x = static_cast<int>((playerQuad_.pos.x - playerQuad_.radius.x) / blockSize);
		nextMap_.leftTop.y = static_cast<int>((playerQuad_.pos.y - playerQuad_.radius.y - speed_) / blockSize);
		nextMap_.rightTop.x = static_cast<int>((playerQuad_.pos.x + playerQuad_.radius.x - 1.0f) / blockSize);
		nextMap_.rightTop.y = static_cast<int>((playerQuad_.pos.y - playerQuad_.radius.y - speed_) / blockSize);

		//ブロックが無ければ進む
		if (m_.map_[nextMap_.leftTop.y][nextMap_.leftTop.x] == 1
			&& m_.map_[nextMap_.rightTop.y][nextMap_.rightTop.x] == 1) {
			playerQuad_.pos.y -= speed_;

			// マップ座標の保存
			prevMap_.leftTop.x = currentMap_.leftTop.x;
			prevMap_.leftTop.y = currentMap_.leftTop.y;
			prevMap_.rightTop.x = currentMap_.rightTop.x;
			prevMap_.rightTop.y = currentMap_.rightTop.y;

			canMoveUp_ = true; // SE用
		} else {
			canMoveUp_ = false;// SE用
		}

		isPressUp_ = true;     // SE用
	} 

	if (keys[DIK_S] && !keys[DIK_W]) {
		//マップチップ上の座標
		nextMap_.leftBottom.x = static_cast<int>((playerQuad_.pos.x - playerQuad_.radius.x) / blockSize);
		nextMap_.leftBottom.y = static_cast<int>((playerQuad_.pos.y + playerQuad_.radius.y - 1.0f + speed_) / blockSize);
		nextMap_.rightBottom.x = static_cast<int>((playerQuad_.pos.x + playerQuad_.radius.x - 1.0f) / blockSize);
		nextMap_.rightBottom.y = static_cast<int>((playerQuad_.pos.y + playerQuad_.radius.y - 1.0f + speed_) / blockSize);
		
		//ブロックが無ければ進む
		if (m_.map_[nextMap_.leftBottom.y][nextMap_.leftBottom.x] == 1
			&& m_.map_[nextMap_.rightBottom.y][nextMap_.rightBottom.x] == 1) {
			playerQuad_.pos.y += speed_;

			// マップ座標の保存
			prevMap_.leftBottom.x = currentMap_.leftBottom.x;
			prevMap_.leftBottom.y = currentMap_.leftBottom.y;
			prevMap_.rightBottom.x = currentMap_.rightBottom.x;
			prevMap_.rightBottom.y = currentMap_.rightBottom.y;

			canMoveDown_ = true;
		} else {
			canMoveDown_ = false;
		}

		isPressDown_ = true;
	}

	if (keys[DIK_A] && !keys[DIK_D]) {
		//マップチップ上の座標
		nextMap_.leftTop.x = static_cast<int>((playerQuad_.pos.x - playerQuad_.radius.x - speed_) / blockSize);
		nextMap_.leftTop.y = static_cast<int>((playerQuad_.pos.y - playerQuad_.radius.y) / blockSize);
		nextMap_.leftBottom.x = static_cast<int>((playerQuad_.pos.x - playerQuad_.radius.x - speed_) / blockSize);
		nextMap_.leftBottom.y = static_cast<int>((playerQuad_.pos.y + playerQuad_.radius.y - 1.0f) / blockSize);

		//ブロックが無ければ進む
		if (m_.map_[nextMap_.leftTop.y][nextMap_.leftTop.x] == 1
			&& m_.map_[nextMap_.leftBottom.y][nextMap_.leftBottom.x] == 1) {
			playerQuad_.pos.x -= speed_;

			// マップ座標の保存
			prevMap_.leftTop.x = currentMap_.leftTop.x;
			prevMap_.leftTop.y = currentMap_.leftTop.y;
			prevMap_.leftBottom.x = currentMap_.leftBottom.x;
			prevMap_.leftBottom.y = currentMap_.leftBottom.y;

			canMoveLeft_ = true;
		} else {
			canMoveLeft_ = false;
		}

		isPressLeft_ = true; // SEとか用に
	} 
	
	if (keys[DIK_D] && !keys[DIK_A]) {
		//マップチップ上の座標
		nextMap_.rightTop.x = static_cast<int>((playerQuad_.pos.x + playerQuad_.radius.x - 1.0f + speed_) / blockSize);
		nextMap_.rightTop.y = static_cast<int>((playerQuad_.pos.y - playerQuad_.radius.y) / blockSize);
		nextMap_.rightBottom.x = static_cast<int>((playerQuad_.pos.x + playerQuad_.radius.x - 1.0f + speed_) / blockSize);
		nextMap_.rightBottom.y = static_cast<int>((playerQuad_.pos.y + playerQuad_.radius.y - 1.0f) / blockSize);
		
		//ブロックが無ければ進む
		if (m_.map_[nextMap_.rightTop.y][nextMap_.rightTop.x] == 1
			&& m_.map_[nextMap_.rightBottom.y][nextMap_.rightBottom.x] == 1) {
			playerQuad_.pos.x += speed_;

			// マップ座標の保存
			prevMap_.rightTop.x = currentMap_.rightTop.x;
			prevMap_.rightTop.y = currentMap_.rightTop.y;
			prevMap_.rightBottom.x = currentMap_.rightBottom.x;
			prevMap_.rightBottom.y = currentMap_.rightBottom.y;

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
	if (m_.map_[prevMap_.leftTop.y][prevMap_.leftTop.x] != m_.map_[currentMap_.leftTop.y][currentMap_.leftTop.x]
		&& m_.map_[prevMap_.leftBottom.y][prevMap_.leftBottom.x] != m_.map_[currentMap_.leftBottom.y][currentMap_.leftBottom.x]
		&& m_.map_[prevMap_.rightTop.y][prevMap_.rightTop.x] != m_.map_[currentMap_.rightTop.y][currentMap_.rightTop.x]
		&& m_.map_[prevMap_.rightBottom.y][prevMap_.rightBottom.x] != m_.map_[currentMap_.rightBottom.y][currentMap_.rightBottom.x]) {
		LeaveTrail();
	}
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

#include "Player.h"

Player::Player() {
	playerQuad_.size = 1;
	playerQuad_.pos = { 80, 80 };
	playerQuad_.radius = { 20, 20 };
	playerQuad_.leftTop = { 60, 60 };
	playerQuad_.leftBottom = { 60, 100 };
	playerQuad_.rightTop = { 100, 60 };
	playerQuad_.rightBottom = { 100, 100 };
	playerQuad_.imagePos = { 0, 0 };
	playerQuad_.imageWidth = 40;
	playerQuad_.imageHeight = 40;
	playerQuad_.image = 0;
	playerQuad_.color = WHITE;

	prevPlayerQuad_ = playerQuad_;

	speed_ = 6;

	canMoveLeft_ = true;
	canMoveRight_ = true;
	canMoveUp_ = true;
	canMoveDown_ = true;

	isPressLeft_ = false;
	isPressRight_ = false; 
	isPressUp_ = false;
	isPressDown_ = false;
}

Player::~Player() {}

void Player::Control(char* keys) {
	// 操作を初期化
	isPressLeft_ = false;
	isPressRight_ = false;
	isPressUp_ = false;
	isPressDown_ = false;

	// 前の座標を保存
	prevPlayerQuad_.pos = playerQuad_.pos;

	// プレイヤーを仮に進ませる
	if (keys[DIK_W] && !keys[DIK_S]) {
		playerQuad_.pos.y -= speed_;
		isPressUp_ = true;
	} else if (keys[DIK_S] && !keys[DIK_W]) {
		playerQuad_.pos.y += speed_;
		isPressDown_ = true;
	}

	if (keys[DIK_A] && !keys[DIK_D]) {
		playerQuad_.pos.x -= speed_;
		isPressLeft_ = true;
	} else if (keys[DIK_D] && !keys[DIK_A]) {
		playerQuad_.pos.x += speed_;
		isPressRight_ = true;
	}
}

void Player::Collision(int map[mapRow][mapColumn]) {
	// 判定を初期化
	canMoveLeft_ = true;
	canMoveRight_ = true;
	canMoveUp_ = true;
	canMoveDown_ = true;

	// 左
	if (map[static_cast<int>(prevPlayerQuad_.leftTop.y / blockSize)]
		[static_cast<int>(playerQuad_.leftTop.x / blockSize)] == 0
		&&
		map[static_cast<int>(prevPlayerQuad_.leftBottom.y / blockSize)]
		[static_cast<int>(playerQuad_.leftBottom.x / blockSize)] == 0
		) {
		canMoveLeft_ = false;
	}
	// 右
	if (map[static_cast<int>(prevPlayerQuad_.rightTop.y / blockSize)]
		[static_cast<int>(playerQuad_.rightTop.x / blockSize)] == 0
		&&
		map[static_cast<int>(prevPlayerQuad_.rightBottom.y / blockSize)]
		[static_cast<int>(playerQuad_.rightBottom.x / blockSize)] == 0
		) {
		canMoveRight_ = false;
	}
	// 上
	if (map[static_cast<int>(playerQuad_.leftTop.y / blockSize)]
		[static_cast<int>(prevPlayerQuad_.leftTop.x / blockSize)] == 0
		&&
		map[static_cast<int>(playerQuad_.rightTop.y / blockSize)]
		[static_cast<int>(prevPlayerQuad_.rightTop.x / blockSize)] == 0
		) {
		canMoveUp_ = false;
	}
	// 下
	if (map[static_cast<int>(playerQuad_.leftBottom.y / blockSize)]
		[static_cast<int>(prevPlayerQuad_.leftBottom.x / blockSize)] == 0
		&&
		map[static_cast<int>(playerQuad_.rightBottom.y / blockSize)]
		[static_cast<int>(prevPlayerQuad_.rightBottom.x / blockSize)] == 0
		) {
		canMoveDown_ = false;
	}
}

void Player::Move() {
	// 最終的な移動処理
	
	// 上方向への移動
	if (canMoveUp_) {
		if (!canMoveLeft_ || !canMoveRight_) {
			if (isPressUp_) {
				playerQuad_.pos.y = prevPlayerQuad_.pos.y - speed_;
			}
		}
	} else {
		// 押し戻し処理
		playerQuad_.pos.y = static_cast<float>(
			(static_cast<int>(playerQuad_.leftTop.y) / blockSize + 1) * blockSize + playerQuad_.radius.y
			);
	}
	// 下方向への移動
	if (canMoveDown_) {
		if (!canMoveLeft_ || !canMoveRight_) {
			if (isPressDown_) {
				playerQuad_.pos.y = prevPlayerQuad_.pos.y + speed_;
			}
		}
	} else {
		// 押し戻し処理
		playerQuad_.pos.y = static_cast<float>(
			(static_cast<int>(playerQuad_.leftTop.y) / blockSize + 1) * blockSize - playerQuad_.radius.y
			);
	}
	// 左方向への移動
	if (canMoveLeft_) {
		if (!canMoveDown_ || !canMoveUp_) {
			if (isPressLeft_) {
				playerQuad_.pos.x = prevPlayerQuad_.pos.x - speed_;
			}
		}
	} else {
		// 押し戻し処理
		playerQuad_.pos.y = static_cast<float>(
			(static_cast<int>(playerQuad_.leftTop.x) / blockSize + 1) * blockSize + playerQuad_.radius.x
			);
	}
	// 右方向への移動
	if (canMoveRight_) {
		if (!canMoveDown_ || !canMoveUp_) {
			if (isPressRight_) {
				playerQuad_.pos.x = prevPlayerQuad_.pos.x + speed_;
			}
		}
	} else {
		// 押し戻し処理
		playerQuad_.pos.x = static_cast<float>(
			(static_cast<int>(playerQuad_.leftTop.x) / blockSize + 1) * blockSize - playerQuad_.radius.x
			);
	}
}

void Player::Update() {
	playerQuad_.leftTop.x = playerQuad_.pos.x - playerQuad_.radius.x;
	playerQuad_.leftTop.y = playerQuad_.pos.y - playerQuad_.radius.y;
	playerQuad_.leftBottom.x = playerQuad_.pos.x - playerQuad_.radius.x;
	playerQuad_.leftBottom.y = playerQuad_.pos.y + playerQuad_.radius.y - 1.0f;
	playerQuad_.rightTop.x = playerQuad_.pos.x + playerQuad_.radius.x - 1.0f;
	playerQuad_.rightTop.y = playerQuad_.pos.y - playerQuad_.radius.y;
	playerQuad_.rightBottom.x = playerQuad_.pos.x + playerQuad_.radius.x - 1.0f;
	playerQuad_.rightBottom.y = playerQuad_.pos.y + playerQuad_.radius.y - 1.0f;

	prevPlayerQuad_.leftTop.x = prevPlayerQuad_.pos.x - prevPlayerQuad_.radius.x;
	prevPlayerQuad_.leftTop.y = prevPlayerQuad_.pos.y - prevPlayerQuad_.radius.y;
	prevPlayerQuad_.leftBottom.x = prevPlayerQuad_.pos.x - prevPlayerQuad_.radius.x;
	prevPlayerQuad_.leftBottom.y = prevPlayerQuad_.pos.y + prevPlayerQuad_.radius.y - 1.0f;
	prevPlayerQuad_.rightTop.x = prevPlayerQuad_.pos.x + prevPlayerQuad_.radius.x - 1.0f;
	prevPlayerQuad_.rightTop.y = prevPlayerQuad_.pos.y - prevPlayerQuad_.radius.y;
	prevPlayerQuad_.rightBottom.x = prevPlayerQuad_.pos.x + prevPlayerQuad_.radius.x - 1.0f;
	prevPlayerQuad_.rightBottom.y = prevPlayerQuad_.pos.y + prevPlayerQuad_.radius.y - 1.0f;
}

void Player::Draw() {
	DrawQuad(playerQuad_);
}

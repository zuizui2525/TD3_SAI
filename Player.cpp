#include "Player.h"

Player::Player() {
	// Quad
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

	// マップ上の番号
	leftTopMap_ = { 1, 1 };
	leftBottomMap_ = { 1, 1 };
	rightTopMap_ = { 1, 1 };
	rightBottomMap_ = { 1, 1 };

	prevLeftTopMap_ = { 1, 1 };
	prevLeftBottomMap_ = { 1, 1 };
	prevRightTopMap_ = { 1, 1 };
	prevRightBottomMap_ = { 1, 1 };

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
	canMoveLeft_ = false;
	canMoveRight_ = false;
	canMoveUp_ = false;
	canMoveDown_ = false;

	// row(y)とcolumn(x)を求める
	//現在の座標
	leftTopMap_ = { 
		static_cast<int>(playerQuad_.leftTop.x / blockSize), 
		static_cast<int>(playerQuad_.leftTop.y / blockSize)
	};
	leftBottomMap_ = {
		static_cast<int>(playerQuad_.leftBottom.x / blockSize),
		static_cast<int>(playerQuad_.leftBottom.y / blockSize)
	};
	rightTopMap_ = {
		static_cast<int>(playerQuad_.rightTop.x / blockSize),
		static_cast<int>(playerQuad_.rightTop.y / blockSize)
	};
	rightBottomMap_ = {
		static_cast<int>(playerQuad_.rightBottom.x / blockSize),
		static_cast<int>(playerQuad_.rightBottom.y / blockSize)
	};
	//保存された座標
	prevLeftTopMap_ = {
		static_cast<int>(prevPlayerQuad_.leftTop.x / blockSize),
		static_cast<int>(prevPlayerQuad_.leftTop.y / blockSize)
	};
	prevLeftBottomMap_ = {
		static_cast<int>(prevPlayerQuad_.leftBottom.x / blockSize),
		static_cast<int>(prevPlayerQuad_.leftBottom.y / blockSize)
	};
	prevRightTopMap_ = {
		static_cast<int>(prevPlayerQuad_.rightTop.x / blockSize),
		static_cast<int>(prevPlayerQuad_.rightTop.y / blockSize)
	};
	prevRightBottomMap_ = {
		static_cast<int>(prevPlayerQuad_.rightBottom.x / blockSize),
		static_cast<int>(prevPlayerQuad_.rightBottom.y / blockSize)
	};

	// 衝突判定
	//左
	if (map[prevLeftTopMap_.y][leftTopMap_.x] == 1
		&& map[prevLeftBottomMap_.y][leftBottomMap_.x] == 1) {
		canMoveLeft_ = true;
	}
	//右
	if (map[prevRightTopMap_.y][rightTopMap_.x] == 1
		&& map[prevRightBottomMap_.y][rightBottomMap_.x] == 1) {
		canMoveRight_ = true;
	}
	//上
	if (map[leftTopMap_.y][prevLeftTopMap_.x] == 1
		&& map[rightTopMap_.y][prevRightTopMap_.x] == 1) {
		canMoveUp_ = true;
	}
	//下
	if (map[leftBottomMap_.y][prevLeftBottomMap_.x] == 1
		&& map[rightBottomMap_.y][prevRightBottomMap_.x] == 1) {
		canMoveDown_ = true;
	}
}

void Player::Move() {
	// 最終的な移動処理
	
	//上方向への移動
	if (canMoveUp_) {
		if (!canMoveLeft_ || !canMoveRight_) {
			if (isPressUp_) {
				playerQuad_.pos.y = prevPlayerQuad_.pos.y - speed_;
			}
		}
	} else {
		//押し戻し処理
		playerQuad_.pos.y = static_cast<float>(
			prevLeftTopMap_.y * blockSize + prevPlayerQuad_.radius.y
			);
	}
	//下方向への移動
	if (canMoveDown_) {
		if (!canMoveLeft_ || !canMoveRight_) {
			if (isPressDown_) {
				playerQuad_.pos.y = prevPlayerQuad_.pos.y + speed_;
			}
		}
	} else {
		//押し戻し処理
		playerQuad_.pos.y = static_cast<float>(
			(prevLeftTopMap_.y + 1) * blockSize - prevPlayerQuad_.radius.y
			);
	}
	//左方向への移動
	if (canMoveLeft_) {
		if (!canMoveDown_ || !canMoveUp_) {
			if (isPressLeft_) {
				playerQuad_.pos.x = prevPlayerQuad_.pos.x - speed_;
			}
		}
	} else {
		//押し戻し処理
		playerQuad_.pos.x = static_cast<float>(
			prevLeftTopMap_.x * blockSize + prevPlayerQuad_.radius.x
			);
	}
	//右方向への移動
	if (canMoveRight_) {
		if (!canMoveDown_ || !canMoveUp_) {
			if (isPressRight_) {
				playerQuad_.pos.x = prevPlayerQuad_.pos.x + speed_;
			}
		}
	} else {
		//押し戻し処理
		playerQuad_.pos.x = static_cast<float>(
			(prevLeftTopMap_.x + 1) * blockSize - prevPlayerQuad_.radius.x
			);
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

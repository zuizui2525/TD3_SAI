#include "Player.h"

Player::Player() {
	player_.size = 1;
	player_.pos = { 80, 80 };
	player_.radius = { 20, 20 };
	player_.leftTop = { 60, 60 };
	player_.leftBottom = { 60, 100 };
	player_.rightTop = { 100, 60 };
	player_.rightBottom = { 100, 100 };
	player_.imagePos = { 0, 0 };
	player_.imageWidth = 40;
	player_.imageHeight = 40;
	player_.image = 0;
	player_.color = WHITE;

	prevPlayer_ = player_;

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
	if (keys[DIK_W] && !keys[DIK_S]) {
		player_.pos.y -= speed_;
		isPressRight_ = true;
	} else if (keys[DIK_S] && !keys[DIK_W]) {
		player_.pos.y += speed_;
		isPressDown_ = true;
	}

	if (keys[DIK_A] && !keys[DIK_D]) {
		player_.pos.x -= speed_;
		isPressLeft_ = true;
	} else if (keys[DIK_D] && !keys[DIK_A]) {
		player_.pos.x += speed_;
		isPressRight_ = true;
	}
}

void Player::Update() {
	player_.leftTop.x = player_.pos.x - player_.radius.x;
	player_.leftTop.y = player_.pos.y - player_.radius.y;
	player_.leftBottom.x = player_.pos.x - player_.radius.x;
	player_.leftBottom.y = player_.pos.y + player_.radius.y;
	player_.rightTop.x = player_.pos.x + player_.radius.x;
	player_.rightTop.y = player_.pos.y - player_.radius.y;
	player_.rightBottom.x = player_.pos.x + player_.radius.x;
	player_.rightBottom.y = player_.pos.y + player_.radius.y;
}

void Player::Draw() {
	DrawQuad(player_);
}

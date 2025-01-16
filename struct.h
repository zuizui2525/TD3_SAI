#pragma once
#include <Novice.h>

///========================================================================
///::::::::::::::::::::::::::::::::::メモ::::::::::::::::::::::::::::::::::
///========================================================================
//宣言時の例:Vector2<int>pos = {}; Vector2<float>pos = {};

//大きさ
enum Size {
	SMALL,
	MEDIUM,
	LARGE
};

//方向
enum Direction {
	UP,
	DOWN,
	LEFT,
	RIGHT
};

template <typename T>
struct Vector2 {
	T x;
	T y;
};

struct Matrix2x2 {
	float m[2][2];
};

struct Matrix3x3 {
	float m[3][3];
};

//4頂点
template <typename T>
struct Vertices4 {
	Vector2<T> leftTop;
	Vector2<T> rightTop;
	Vector2<T> leftBottom;
	Vector2<T> rightBottom;
};

//[ 線の構造体 ]
//start: 始点座標
//end: 終点座標
//color: 色
struct Line {
	Vector2<float> start;
	Vector2<float> end;
	int color;
};

//[ 四角形の構造体 ]
//pos: 左上座標
//width: 横幅
//height: 縦幅
//angle: 角度
//color: 色
//shape: 塗りつぶしモード
struct Box {
	Vector2<float> pos;
	float width;
	float height;
	float angle;
	int color;
	FillMode shape;
};

//[ 円の構造体 ]
//pos: 中心座標
//radius: 半径
//angle: 角度
//color: 色
//shape: 塗りつぶしモード
struct Circle {
	Vector2<float> pos;
	Vector2<float> radius;
	float angle;
	int color;
	FillMode shape;
};

//[ スプライトの構造体 ]
//pos: 左上座標
//image: テクスチャハンドル
//scale: 倍率
//angle: 角度
//color: 色
struct Sprite {
	Vector2<float> pos;
	int image;
	Vector2<float> scale;
	float angle;
	int color;
};

//[ 四角形描画の構造体 ]
//pos: 中心座標, radius: 半径
//leftTop: 左上の点の座標, rightTop: 右上の点の座標
//leftBottom: 左下の点の座標, rightBottom: 右下の点の座標
//imagePos: 画像の左上座標
//imageWidth: 画像の横幅
//imageHeight: 画像の縦幅
//image: テクスチャハンドル
//color: 色
struct Quad {
	float size;
	Vector2<float> pos;
	Vector2<float> radius;
	Vector2<float> leftTop;
	Vector2<float> rightTop;
	Vector2<float> leftBottom;
	Vector2<float> rightBottom;
	Vector2<int> imagePos;
	int imageWidth;
	int imageHeight;
	int image;
	int color;
};

struct Images {
	int blocks = Novice::LoadTexture("./Resources./images./blocks.png");
	int player = Novice::LoadTexture("./Resources./images./Player.png");
	int enemy_mie = Novice::LoadTexture("./Resources./images./EnemyMie.png");
	int enemy_moo = Novice::LoadTexture("./Resources./images./EnemyMoo.png");
};
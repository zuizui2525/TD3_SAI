#pragma once
#include "struct.h"

#pragma region 色のサンプル
#define YELLOW 0xffdc00FF //黄色
#define PINK 0xff66ccFF //ピンク色
#define PURPLE 0xd6adffFF //紫色
#define GRAY 0x7d7d7dFF //灰色
#pragma endregion

#pragma region 描画関数
/// <summary>
/// 簡易的な線の描画をする関数
/// </summary>
/// <param name="line">線の構造体</param>
void DrawLine(Line line);

/// <summary>
/// 簡易的な四角形の描画をする関数
/// </summary>
/// <param name="box">四角形の構造体</param>
void DrawBox(Box box);

/// <summary>
/// 簡易的な円の描画をする関数
/// </summary>
/// <param name="circle">円の構造体</param>
void DrawCircle(Circle circle);

/// <summary>
/// 簡易的なスプライトの描画をする関数
/// </summary>
/// <param name="sprite">スプライトの構造体</param>
void DrawSprite(Sprite sprite);

/// <summary>
/// 簡易的な四角形描画の描画をする関数
/// </summary>
/// <param name="quad">四角形描画の構造体</param>
void DrawQuad(Quad quad);

/// <summary>
/// Quadをアニメーションする関数
/// </summary>
/// <param name="quad">四角形描画の構造体</param>
/// <param name="numberOfSheet">アニメーションのコマ数</param>
/// <param name="AnimationSpeed">画像が切り替わる速度</param>
/// <returns>画像の左上の座標(アニメーション済み)</returns>
void DrawAnimationQuad(Quad quad, int numberOfSheet, int AnimationSpeed);
#pragma endregion

#pragma region 行列関係の関数
/// <summary>
/// 拡大縮小行列を作成する関数
/// </summary>
/// <param name="Scale">拡縮成分</param>
/// <returns>拡大縮小行列</returns>
Matrix3x3 MakeScaleMatrix(Vector2<float> Scale);

/// <summary>
/// 回転行列を作成する関数
/// </summary>
/// <param name="theta">角度成分</param>
/// <returns>回転行列</returns>
Matrix3x3 MakeRotateMatrix(float theta);

/// <summary>
/// 平行移動行列を作成する関数
/// </summary>
/// <param name="translate">平行移動成分</param>
/// <returns>平行移動行列</returns>
Matrix3x3 MakeTranslateMatrix(Vector2<float> translate);

/// <summary>
/// アフィン変換行列を作成する関数
/// </summary>
/// <param name="scale">拡縮成分</param>
/// <param name="theta">角度成分</param>
/// <param name="translate">平行移動成分</param>
/// <returns>アフィン変換行列</returns>
Matrix3x3 MakeAffineMatrix(Vector2<float> scale, float theta, Vector2<float> translate);

/// <summary>
/// 逆行列を作成する関数
/// </summary>
/// <param name="matrix">逆行列にしたい行列</param>
/// <returns>逆行列</returns>
Matrix3x3 MakeInverseMatrix(Matrix3x3 matrix);

/// <summary>
/// 正射影行列を作成する関数
/// </summary>
/// <param name="left">カメラの左</param>
/// <param name="top">カメラの上</param>
/// <param name="right">カメラの右</param>
/// <param name="bottom">カメラの下</param>
/// <returns>正射影行列</returns>
Matrix3x3 MakeOrthographicMatrix(float left, float top, float right, float bottom);

/// <summary>
/// ビューポート行列を作る関数
/// </summary>
/// <param name="left">カメラの左</param>
/// <param name="top">カメラの上</param>
/// <param name="width">横幅</param>
/// <param name="height">縦幅</param>
/// <returns>ビューポート行列</returns>
Matrix3x3 MakeViewportMatrix(float left, float top, float width, float height);

/// <summary>
/// Matrix3x3を積算する関数
/// </summary>
/// <param name="num1">掛けられる値①</param>
/// <param name="num2">掛ける値②</param>
/// <returns>計算結果</returns>
Matrix3x3 MultiplyMatrix(Matrix3x3 num1, Matrix3x3 num2);

/// <summary>
/// 2次元ベクトルを同次座標に変換する関数
/// </summary>
/// <param name="vector">2次元ベクトル</param>
/// <param name="matrix">3x3行列</param>
/// <returns>Matrix3x3に変換</returns>
Vector2<float> Transform(Vector2<float> vector, Matrix3x3 matrix);
#pragma endregion

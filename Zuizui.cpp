#include <math.h>
#include <assert.h>
#include "Zuizui.h"

#pragma region 描画関数
//簡易的な線の描画をする関数
void DrawLine(Line line) {
	Novice::DrawLine(
		static_cast<int>(line.start.x), static_cast<int>(line.start.y),
		static_cast<int>(line.end.x), static_cast<int>(line.end.y),
		static_cast<unsigned int>(line.color)
	);
}

//簡易的な四角形の描画をする関数
void DrawBox(Box box) {
	Novice::DrawBox(
		static_cast<int>(box.pos.x), static_cast<int>(box.pos.y),
		static_cast<int>(box.width), static_cast<int>(box.height),
		static_cast<float>(box.angle),
		static_cast<unsigned int>(box.color),
		static_cast<FillMode>(box.shape)
	);
}

//簡易的な円の描画をする関数
void DrawCircle(Circle circle) {
	Novice::DrawEllipse(
		static_cast<int>(circle.pos.x), static_cast<int>(circle.pos.y),
		static_cast<int>(circle.radius.x), static_cast<int>(circle.radius.y),
		static_cast<float>(circle.angle),
		static_cast<unsigned int>(circle.color),
		static_cast<FillMode>(circle.shape)
	);
}

//簡易的なスプライトの描画をする関数
void DrawSprite(Sprite sprite) {
	Novice::DrawSprite(
		static_cast<int>(sprite.pos.x), static_cast<int>(sprite.pos.y),
		static_cast<int>(sprite.image),
		static_cast<float>(sprite.scale.x), static_cast<float>(sprite.scale.y),
		static_cast<float>(sprite.angle),
		static_cast<unsigned int>(sprite.color)
	);
}

//簡易的な四角形描画の描画をする関数
void DrawQuad(Quad quad) {
	Novice::DrawQuad(
		static_cast<int>(quad.leftTop.x), static_cast<int>(quad.leftTop.y),
		static_cast<int>(quad.rightTop.x), static_cast<int>(quad.rightTop.y),
		static_cast<int>(quad.leftBottom.x), static_cast<int>(quad.leftBottom.y),
		static_cast<int>(quad.rightBottom.x), static_cast<int>(quad.rightBottom.y),
		static_cast<int>(quad.imagePos.x * quad.size), static_cast<int>(quad.imagePos.y),
		static_cast<int>(quad.imageWidth), static_cast<int>(quad.imageHeight),
		static_cast<int>(quad.image),
		static_cast<unsigned int>(quad.color)
	);
}

//Quadをアニメーションして描画する関数
int animationTimer = 0;
int animationNumber = 1;
void DrawAnimationQuad(Quad quad, int numberOfSheet, int animationSpeed) {
	if (animationTimer > 0) {
		animationTimer--;
	} else {
		animationNumber++;
		animationTimer = animationSpeed;
	}
	if (animationNumber >= numberOfSheet) {
		animationNumber = 0;
	}
	quad.imagePos = { animationNumber * quad.imageWidth,0 };
	DrawQuad(quad);
}
#pragma endregion

#pragma region 行列関係の関数
//拡大縮小行列
Matrix3x3 MakeScaleMatrix(Vector2<float> scale) {
	Matrix3x3 num = {
		{
		{scale.x,0.0f,0.0f},
		{0.0f,scale.y,0.0f},
		{0.0f,0.0f,1.0f}
		}
	};
	return num;
}

//回転行列
Matrix3x3 MakeRotateMatrix(float theta) {
	Matrix3x3 num = {
		{
		{cosf(theta),sinf(theta),0.0f},
		{-sinf(theta),cosf(theta),0.0f},
		{0.0f,0.0f,1.0f}
		}
	};
	return num;
}

//平行移動行列
Matrix3x3 MakeTranslateMatrix(Vector2<float> translate) {
	Matrix3x3 num = {
		{
		{1.0f,0.0f,0.0f},
		{0.0f,1.0f,0.0f},
		{translate.x,translate.y,1.0f}
		}
	};
	return num;
}

//アフィン変換行列
Matrix3x3 MakeAffineMatrix(Vector2<float> scale, float theta, Vector2<float> translate) {
	Matrix3x3 num = {
		{
		{scale.x * cosf(theta),scale.x * sinf(theta), 0.0f},
		{scale.y * -sinf(theta),scale.y * cosf(theta),0.0f},
		{translate.x,translate.y,1.0f}
		}
	};
	return num;
}

//逆行列
Matrix3x3 MakeInverseMatrix(Matrix3x3 num) {
	Matrix3x3 num1;
	num1.m[0][0] = (num.m[1][1] * num.m[2][2] - num.m[1][2] * num.m[2][1]) * (1.0f / (num.m[0][0] * num.m[1][1] * num.m[2][2] + num.m[0][1] * num.m[1][2] * num.m[2][0] + num.m[0][2] * num.m[1][0] * num.m[2][1] - num.m[0][2] * num.m[1][1] * num.m[2][0] - num.m[0][1] * num.m[1][0] * num.m[2][2] - num.m[0][0] * num.m[1][2] * num.m[2][1]));
	num1.m[0][1] = -(num.m[0][1] * num.m[2][2] - num.m[0][2] * num.m[2][1]) * (1.0f / (num.m[0][0] * num.m[1][1] * num.m[2][2] + num.m[0][1] * num.m[1][2] * num.m[2][0] + num.m[0][2] * num.m[1][0] * num.m[2][1] - num.m[0][2] * num.m[1][1] * num.m[2][0] - num.m[0][1] * num.m[1][0] * num.m[2][2] - num.m[0][0] * num.m[1][2] * num.m[2][1]));
	num1.m[0][2] = (num.m[0][1] * num.m[1][2] - num.m[0][2] * num.m[1][1]) * (1.0f / (num.m[0][0] * num.m[1][1] * num.m[2][2] + num.m[0][1] * num.m[1][2] * num.m[2][0] + num.m[0][2] * num.m[1][0] * num.m[2][1] - num.m[0][2] * num.m[1][1] * num.m[2][0] - num.m[0][1] * num.m[1][0] * num.m[2][2] - num.m[0][0] * num.m[1][2] * num.m[2][1]));
	num1.m[1][0] = -(num.m[1][0] * num.m[2][2] - num.m[1][2] * num.m[2][0]) * (1.0f / (num.m[0][0] * num.m[1][1] * num.m[2][2] + num.m[0][1] * num.m[1][2] * num.m[2][0] + num.m[0][2] * num.m[1][0] * num.m[2][1] - num.m[0][2] * num.m[1][1] * num.m[2][0] - num.m[0][1] * num.m[1][0] * num.m[2][2] - num.m[0][0] * num.m[1][2] * num.m[2][1]));
	num1.m[1][1] = (num.m[0][0] * num.m[2][2] - num.m[0][2] * num.m[2][0]) * (1.0f / (num.m[0][0] * num.m[1][1] * num.m[2][2] + num.m[0][1] * num.m[1][2] * num.m[2][0] + num.m[0][2] * num.m[1][0] * num.m[2][1] - num.m[0][2] * num.m[1][1] * num.m[2][0] - num.m[0][1] * num.m[1][0] * num.m[2][2] - num.m[0][0] * num.m[1][2] * num.m[2][1]));
	num1.m[1][2] = -(num.m[0][0] * num.m[1][2] - num.m[0][2] * num.m[1][0]) * (1.0f / (num.m[0][0] * num.m[1][1] * num.m[2][2] + num.m[0][1] * num.m[1][2] * num.m[2][0] + num.m[0][2] * num.m[1][0] * num.m[2][1] - num.m[0][2] * num.m[1][1] * num.m[2][0] - num.m[0][1] * num.m[1][0] * num.m[2][2] - num.m[0][0] * num.m[1][2] * num.m[2][1]));
	num1.m[2][0] = (num.m[1][0] * num.m[2][1] - num.m[1][1] * num.m[2][0]) * (1.0f / (num.m[0][0] * num.m[1][1] * num.m[2][2] + num.m[0][1] * num.m[1][2] * num.m[2][0] + num.m[0][2] * num.m[1][0] * num.m[2][1] - num.m[0][2] * num.m[1][1] * num.m[2][0] - num.m[0][1] * num.m[1][0] * num.m[2][2] - num.m[0][0] * num.m[1][2] * num.m[2][1]));
	num1.m[2][1] = -(num.m[0][0] * num.m[2][1] - num.m[0][1] * num.m[2][0]) * (1.0f / (num.m[0][0] * num.m[1][1] * num.m[2][2] + num.m[0][1] * num.m[1][2] * num.m[2][0] + num.m[0][2] * num.m[1][0] * num.m[2][1] - num.m[0][2] * num.m[1][1] * num.m[2][0] - num.m[0][1] * num.m[1][0] * num.m[2][2] - num.m[0][0] * num.m[1][2] * num.m[2][1]));
	num1.m[2][2] = (num.m[0][0] * num.m[1][1] - num.m[0][1] * num.m[1][0]) * (1.0f / (num.m[0][0] * num.m[1][1] * num.m[2][2] + num.m[0][1] * num.m[1][2] * num.m[2][0] + num.m[0][2] * num.m[1][0] * num.m[2][1] - num.m[0][2] * num.m[1][1] * num.m[2][0] - num.m[0][1] * num.m[1][0] * num.m[2][2] - num.m[0][0] * num.m[1][2] * num.m[2][1]));
	return num1;
}

//正射影行列
Matrix3x3 MakeOrthographicMatrix(float left, float top, float right, float bottom) {
	Matrix3x3 num1;
	num1.m[0][0] = 2.0f / (right - left);
	num1.m[0][1] = 0.0f;
	num1.m[0][2] = 0.0f;
	num1.m[1][0] = 0.0f;
	num1.m[1][1] = 2.0f / (top - bottom);
	num1.m[1][2] = 0.0f;
	num1.m[2][0] = (left + right) / (left - right);
	num1.m[2][1] = (top + bottom) / (bottom - top);
	num1.m[2][2] = 1.0f;
	return num1;
}

//ビューポート行列
Matrix3x3 MakeViewportMatrix(float left, float top, float width, float height) {
	Matrix3x3 num1;
	num1.m[0][0] = width / 2.0f;
	num1.m[0][1] = 0.0f;
	num1.m[0][2] = 0.0f;
	num1.m[1][0] = 0.0f;
	num1.m[1][1] = -height / 2.0f;
	num1.m[1][2] = 0.0f;
	num1.m[2][0] = left + (width / 2.0f);
	num1.m[2][1] = top + (height / 2.0f);
	num1.m[2][2] = 1.0f;
	return num1;
}

//行列の積算
Matrix3x3 MultiplyMatrix(Matrix3x3 num1, Matrix3x3 num2) {
	Matrix3x3 total = {
		{
		{num1.m[0][0] * num2.m[0][0] + num1.m[0][1] * num2.m[1][0] + num1.m[0][2] * num2.m[2][0],num1.m[0][0] * num2.m[0][1] + num1.m[0][1] * num2.m[1][1] + num1.m[0][2] * num2.m[2][1],num1.m[0][0] * num2.m[0][2] + num1.m[0][1] * num2.m[1][2] + num1.m[0][2] * num2.m[2][2]},
		{num1.m[1][0] * num2.m[0][0] + num1.m[1][1] * num2.m[1][0] + num1.m[1][2] * num2.m[2][0],num1.m[1][0] * num2.m[0][1] + num1.m[1][1] * num2.m[1][1] + num1.m[1][2] * num2.m[2][1],num1.m[1][0] * num2.m[0][2] + num1.m[1][1] * num2.m[1][2] + num1.m[1][2] * num2.m[2][2]},
		{num1.m[2][0] * num2.m[0][0] + num1.m[2][1] * num2.m[1][0] + num1.m[2][2] * num2.m[2][0],num1.m[2][0] * num2.m[0][1] + num1.m[2][1] * num2.m[1][1] + num1.m[2][2] * num2.m[2][1],num1.m[2][0] * num2.m[0][2] + num1.m[2][1] * num2.m[1][2] + num1.m[2][2] * num2.m[2][2]}
		}
	};
	return total;
}

//2次元ベクトルを同次座標に変換
Vector2<float> Transform(Vector2<float> vector, Matrix3x3 matrix) {
	Vector2<float> result;
	result.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + 1.0f * matrix.m[2][0];
	result.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + 1.0f * matrix.m[2][1];
	float w = vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + 1.0f * matrix.m[2][2];
	assert(w != 0.0f);
	result.x /= w;
	result.y /= w;
	return result;
}
#pragma endregion

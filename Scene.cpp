#include "Scene.h"


Scene::Scene() {
	currentScene = TITLE; // 最初はタイトルシーン
}

Scene::~Scene() {

}

void Scene::Update() {
	switch (currentScene) {
		// タイトルシーン
	case TITLE:

		// ボタンが押されたとき
		if (currentScene) {
			CleanupScene(TITLE);
			ChangeScene(STAGESELECT);
		}
		
		break;
		// ステージセレクトシーン
	case STAGESELECT:

		// ステージを選択したとき
		if (currentScene) {
			CleanupScene(STAGESELECT);
			ChangeScene(STAGESELECT);
		}

		break;
		// ゲームシーン
	case GAME:

		// プレイヤーがやられたとき
		if (currentScene) {
			CleanupScene(GAME);
			ChangeScene(GAMEOVER);
		}

		break;
		// ゲームクリアシーン
	case GAMECLEAR:

		// ボタンが押されたとき
		if (currentScene) {
			CleanupScene(GAMECLEAR);
			ChangeScene(TITLE);
		}

		break;
		// ゲームオーバーシーン
	case GAMEOVER:

		// ボタンが押されたとき
		if (currentScene) {
			CleanupScene(GAMEOVER);
			ChangeScene(TITLE);
		}

		break;
	}
}

void Scene::ChangeScene(SceneType newScene) {
	switch (newScene) {
		// タイトルシーン
	case TITLE:
		// 初期化処理
		InitializeScene(newScene);
		
		// 現在のシーンの更新
		currentScene = TITLE;

		break;
		// ステージセレクトシーン
	case STAGESELECT:
		// 初期化処理
		InitializeScene(newScene);

		// 現在のシーンの更新
		currentScene = STAGESELECT;

		break;
		// ゲームシーン
	case GAME:
		// 初期化処理
		InitializeScene(newScene);

		// 現在のシーンの更新
		currentScene = GAME;

		break;
		// ゲームクリアシーン
	case GAMECLEAR:
		// 初期化処理
		InitializeScene(newScene);

		// 現在のシーンの更新
		currentScene = GAMECLEAR;

		break;
		// ゲームオーバーシーン
	case GAMEOVER:
		// 初期化処理
		InitializeScene(newScene);

		// 現在のシーンの更新
		currentScene = GAMEOVER;

		break;
	}
}

void Scene::InitializeScene(SceneType scene) {
	switch (scene) {
		// タイトルシーン
	case TITLE:

		break;
		// ステージセレクトシーン
	case STAGESELECT:

		break;
		// ゲームシーン
	case GAME:

		break;
		// ゲームクリアシーン
	case GAMECLEAR:

		break;
		// ゲームオーバーシーン
	case GAMEOVER:

		break;
	}
}

void Scene::CleanupScene(SceneType scene) {
	switch (scene) {
		// タイトルシーン
	case TITLE:

		break;
		// ステージセレクトシーン
	case STAGESELECT:

		break;
		// ゲームシーン
	case GAME:

		break;
		// ゲームクリアシーン
	case GAMECLEAR:

		break;
		// ゲームオーバーシーン
	case GAMEOVER:

		break;
	}
}
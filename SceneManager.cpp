#include "SceneManager.h"
#include "mapCode.h"


SceneManager::SceneManager() {
    currentScene = TITLE;
    transitioning_ = false;
}

SceneManager::~SceneManager() {}

void SceneManager::HandleInput(char* keys, char* preKeys) {
    if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {  // SPACEキーが押された場合
        // シーンを切り替え
        currentScene = GetCurrentScene();
        if (currentScene == TITLE) {
            ChangeScene(GAME);
        } else if (currentScene == CLEAR) {
            ChangeScene(TITLE);
        } else if (currentScene == GAMEOVER) {
            ChangeScene(TITLE);
        }
    }

    if (c_->takeCount >= kMaxCoinNum) {
        if (currentScene == GAME) {
            ChangeScene(CLEAR);
        }
    }
    if (!player_->isAlive_) {
        if (currentScene == GAME) {
            ChangeScene(GAMEOVER);
        }
    }

}

// シーン遷移
void SceneManager::ChangeScene(SceneType newScene) {
    if (transitioning_) { return; }  // 遷移中なら無視

    transitioning_ = true;

    CleanupScene(currentScene);  // 現在のシーンをクリーンアップ
    currentScene = newScene;
    InitializeScene(newScene);  // 新しいシーンを初期化

    transitioning_ = false;
}

// シーンの初期化処理
void SceneManager::InitializeScene(SceneType scene) {
    switch (scene) {
    case TITLE:
        // タイトル画面の初期化
        break;
    case STAGESELECT:
        // ステージ選択画面の初期化
        break;
    case GAME:
        // ゲームの初期化
        m_->changeTheMap(map1);

        c_->Spawn(coins1);

        c_->takeCount = 0;
        for (int i = 0; i < kMaxCoinNum; i++) {
            c_->isTaken_[i] = false;
        }

        player_->Initialize(1, 1);
        break;
    case CLEAR:
        // ゲームクリアの処理
        break;
    case GAMEOVER:
        // ゲームオーバーの処理
        break;
    }
}

// シーンのクリーンアップ処理
void SceneManager::CleanupScene(SceneType scene) {
    switch (scene) {
    case TITLE:
        // タイトル画面のクリーンアップ
        break;
    case STAGESELECT:
        // ステージ選択画面のクリーンアップ
        break;
    case GAME:
        // ゲームのクリーンアップ
        break;
    case CLEAR:
        // ゲームクリアのクリーンアップ
        break;
    case GAMEOVER:
        // ゲームオーバーのクリーンアップ
        break;
    }
}

// デバッグ用に現在のシーンを表示
void SceneManager::PrintCurrentScene() {
    switch (currentScene) {
    case TITLE:
        Novice::ScreenPrintf(1300, 600, "Current Scene: TITLE");
        break;
    case STAGESELECT:
        Novice::ScreenPrintf(1300, 600, "Current Scene: STAGESELECT");
        break;
    case GAME:
        Novice::ScreenPrintf(1300, 600, "Current Scene: GAME");
        break;
    case CLEAR:
        Novice::ScreenPrintf(1300, 600, "Current Scene: CLEAR");
        break;
    case GAMEOVER:
        Novice::ScreenPrintf(1300, 600, "Current Scene: GAMEOVER");
        break;
    }
}
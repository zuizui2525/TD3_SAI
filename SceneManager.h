#pragma once
#include <Novice.h>
#include "Player.h"
#include "map.h"
#include "Coin.h"

class SceneManager {
public:
    // ゲームのシーンの種類
    enum SceneType {
        TITLE,
        STAGESELECT,
        GAME,
        CLEAR,
        GAMEOVER
    };

    Player* player_;

    Map* m_;
    Coin* c_;

private:
    SceneType currentScene;  // 現在のシーン
    int transitioning_;       // シーン遷移中かどうか

public:
    // コンストラクタとデストラクタ
    SceneManager();
    ~SceneManager();

    void HandleInput(char* keys, char* preKeys);

    // 現在のシーンを取得
    SceneType GetCurrentScene() { return currentScene; }

    // シーン遷移
    void ChangeScene(SceneType newScene);

    // シーンの初期化処理
    void InitializeScene(SceneType scene);

    // シーンのクリーンアップ処理
    void CleanupScene(SceneType scene);

    // デバッグ用に現在のシーンを表示
    void PrintCurrentScene();
};


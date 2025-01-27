#pragma once


class Scene {
public:
    // ゲームのシーンの種類
    enum SceneType {
        TITLE,
        STAGESELECT,
        GAME,
        GAMECLEAR,
        GAMEOVER
    };

private:
    SceneType currentScene;  // 現在のシーン
    int transitioning_;      // シーン遷移中かどうか

public:
    // コンストラクタとデストラクタ
    Scene();
    ~Scene();

    void Update();

    // 現在のシーンを取得
    SceneType GetCurrentScene() { return currentScene; }

    // シーン遷移
    void ChangeScene(SceneType newScene);

    // シーンの初期化処理
    void InitializeScene(SceneType scene);

    // シーンのクリーンアップ処理
    void CleanupScene(SceneType scene);
};


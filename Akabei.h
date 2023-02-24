#pragma once
#include "Engine/GameObject.h"
#include "Stage.h"

static const std::pair<int, int> DIRECCIONS[] = {
    { -1, 0 },
    { +1, 0 },
    { 0, -1 },
    { 0, +1 }
};

static enum Move
{
    UP_ROW = 0,
    DOWN_ROW,
    LEFT_COL,
    RIGHT_COL,
};

//◆◆◆を管理するクラス
class Akabei : public GameObject
{
    int hModel_;    //モデル番号

    Stage* pStage = nullptr;

public:
    //コンストラクタ
    Akabei(GameObject* parent);

    //デストラクタ
    ~Akabei();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;

    //Astar法での探索
    void Astar();

};

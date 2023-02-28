#pragma once
#include "Engine/GameObject.h"
#include "Stage.h"

class Player;

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

enum MODE
{
    TERRITORIAL_MODE = 0,
    TRACKING_MODE,
};

//◆◆◆を管理するクラス
class Akabei : public GameObject
{
    int hModel_;    //モデル番号
    Stage* pStage = nullptr;
    Player* pPlayer = nullptr;
    std::list<Cell> routeList;
    int mode;
    Cell prevCell;

    const float VIEWING_ANGLE = 0.3f;//視野角（-1から1）
    const float NEAR_DISTANCE = 7.0f;

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

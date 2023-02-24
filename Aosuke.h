#pragma once
#include "Engine/GameObject.h"
#include "Stage.h"

//◆◆◆を管理するクラス
class Aosuke : public GameObject
{
    int hModel_;    //モデル番号

    Stage* pStage = nullptr;

    std::pair<int, int> Map_Start;
    std::pair<int, int> MAP_GOAL;

public:
    //コンストラクタ
    Aosuke(GameObject* parent);

    //デストラクタ
    ~Aosuke();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;
};

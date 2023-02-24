#pragma once
#include "Engine/GameObject.h"
#include "Stage.h"

//◆◆◆を管理するクラス
class Pinky : public GameObject
{
    int hModel_;    //モデル番号

    Stage* pStage = nullptr;
public:
    //コンストラクタ
    Pinky(GameObject* parent);

    //デストラクタ
    ~Pinky();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;
};

#pragma once
#include "Engine/GameObject.h"
#include "Stage.h"

//◆◆◆を管理するクラス
class Guzuta : public GameObject
{
    int hModel_;    //モデル番号

    Stage* pStage = nullptr;
public:
    //コンストラクタ
    Guzuta(GameObject* parent);

    //デストラクタ
    ~Guzuta();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;
};

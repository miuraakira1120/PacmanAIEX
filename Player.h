#pragma once
#include "Engine/GameObject.h"
#include "Stage.h"

//◆◆◆を管理するクラス
class Player : public GameObject
{
    int hModel_;    //モデル番号
    Stage* pStage = nullptr;
    std::pair<int, int> nowMapPos; //first = x, second = z;
    std::pair<int, int> prevMapPos;//first = x, second = z;

public:

    //コンストラクタ
    Player(GameObject* parent);

    //デストラクタ
    ~Player();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画

    void Draw() override;

    //開放
    void Release() override;

    //何かに当たった
    //引数：pTarget 当たった相手
    void OnCollision(GameObject* pTarget) override;

};
#pragma once

#include "Engine/GameObject.h"


//◆◆◆を管理するクラス

class Wall : public GameObject

{
    int hModel_;    //モデル番号

public:

    //コンストラクタ

    Wall(GameObject* parent);


    //デストラクタ

    ~Wall();


    //初期化

    void Initialize() override;


    //更新

    void Update() override;


    //描画

    void Draw() override;


    //開放

    void Release() override;

};
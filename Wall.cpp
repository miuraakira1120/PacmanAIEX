#include "Wall.h"
#include "Engine/Model.h"

//コンストラクタ

Wall::Wall(GameObject* parent)

    :GameObject(parent, "Wall"), hModel_(-1)

{

}


//デストラクタ

Wall::~Wall()

{

}


//初期化

void Wall::Initialize()

{
    //モデルデータのロード
    hModel_ = Model::Load("Wall.fbx");
    assert(hModel_ >= 0);
}


//更新

void Wall::Update()

{

}


//描画

void Wall::Draw()

{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}


//開放

void Wall::Release()

{

}
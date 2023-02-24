#include "Guzuta.h"
#include "Engine/Model.h"
#include "Engine/SphereCollider.h"

//コンストラクタ
Guzuta::Guzuta(GameObject* parent)
    :GameObject(parent, "Guzuta"), hModel_(-1)
{
}

//デストラクタ
Guzuta::~Guzuta()
{
}

//初期化
void Guzuta::Initialize()
{
    //モデルデータのロード
    hModel_ = Model::Load("guzuta.fbx");
    assert(hModel_ >= 0);

    pStage = (Stage*)FindObject("Stage");
    assert(pStage != nullptr);

    transform_.position_.x = 10.5;
    transform_.position_.z = 12.5;

    SphereCollider* collision = new SphereCollider(XMFLOAT3(0, 0, 0), 0.3f);
    AddCollider(collision);
}

//更新
void Guzuta::Update()
{
    //transform_.position_.x += 0.1;
    XMVECTOR prevPosition = XMLoadFloat3(&transform_.position_);

    //現在の位置ベクトル
    XMVECTOR nowPosition = XMLoadFloat3(&transform_.position_);

    //移動ベクトルを求める
    XMVECTOR move = nowPosition - prevPosition;

    //移動ベクトルの長さを測る
    XMVECTOR lenght = XMVector3Length(move);
    //0.1以上移動していたら回転処理
    if (XMVectorGetY(lenght) > 0.1)
    {

        //ベクトルを正規化する
        move = XMVector3Normalize(move);

        //基準となる奥行きのベクトル
        XMVECTOR front = { 0,0,1,0 };

        //frontとmoveの内積を求める
        XMVECTOR vecDot = XMVector3Dot(front, move);
        float dot = XMVectorGetY(vecDot);

        //向いている角度を求める
        float angle = acos(dot);

        //frontとmoveの外積を求める
        XMVECTOR cross = XMVector3Cross(front, move);

        //外積の結果のYがマイナス　＝　下向き　＝　左に進んでいる
        if (XMVectorGetY(cross) < 0)
        {
            angle *= -1;
        }

        //そのぶん回転させる
        transform_.rotate_.y = angle * (180.0f / 3.14f);
    }

    /////////衝突判定////////////

    //壁との衝突判定
    int checkX, checkZ;

    //右
    checkX = (int)(transform_.position_.x + 0.3f);
    checkZ = (int)(transform_.position_.z);

    if (pStage->IsWall(checkX, checkZ))
    {
        transform_.position_.x = (float)((int)(transform_.position_.x + 0.5f) - 0.3f);

    }
    //左
    checkX = (int)(transform_.position_.x - 0.3f);
    if (pStage->IsWall(checkX, checkZ))
    {
        transform_.position_.x = (float)((int)(transform_.position_.x + 0.5) + 0.3f);

    }
    //上
    checkX = (int)(transform_.position_.x);
    checkZ = (int)(transform_.position_.z - 0.3f);
    if (pStage->IsWall(checkX, checkZ))
    {
        transform_.position_.z = (float)((int)(transform_.position_.z + 0.5) + 0.3f);

    }

    //下
    checkZ = (int)(transform_.position_.z + 0.3f);
    if (pStage->IsWall(checkX, checkZ))
    {
        transform_.position_.z = (float)((int)(transform_.position_.z + 0.5f) - 0.3f);
    }
}

//描画
void Guzuta::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//開放
void Guzuta::Release()
{
}

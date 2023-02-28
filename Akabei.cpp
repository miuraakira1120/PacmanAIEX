#include "Akabei.h"
#include "Engine/Model.h"
#include "Engine/SphereCollider.h"
#include <queue>
#include "Player.h"

using std::vector;
using std::pair;


//コンストラクタ
Akabei::Akabei(GameObject* parent)
    :GameObject(parent, "Akabei"), hModel_(-1),mode(TERRITORIAL_MODE), prevCell(-1,-1)
{
}

//デストラクタ
Akabei::~Akabei()
{
}

//初期化
void Akabei::Initialize()
{
    //モデルデータのロード
    hModel_ = Model::Load("akabei.fbx");
    assert(hModel_ >= 0);

    pStage = (Stage*)FindObject("Stage");
    assert(pStage != nullptr);

    pPlayer = (Player*)FindObject("Player");
    assert(pPlayer != nullptr);
    

    transform_.position_.x = 0.5f;
    transform_.position_.z = 0.5f;

    Cell cellPPos = { (int)pPlayer->GetPosition().x, (int)pPlayer->GetPosition().z };
    Cell cellEPos = { (int)transform_.position_.x, (int)transform_.position_.z };
    routeList = pStage->AStar(cellEPos, cellPPos);

    //リストの先頭を削除
    routeList.pop_front();

    SphereCollider* collision = new SphereCollider(XMFLOAT3(0, 0, 0), 0.3f);
    AddCollider(collision);
}

//更新
void Akabei::Update()
{
    XMVECTOR prevPosition = XMLoadFloat3(&transform_.position_);

    //mode = TRACKING_MODE;
    switch (mode)
    {
    case TERRITORIAL_MODE :
        //もし目的地にたどり着いたら
        if ((int)transform_.position_.x == routeList.front().x &&
            (int)transform_.position_.z == routeList.front().y)
        {
            routeList.clear();
            routeList.push_front(pStage->RandEdgesCell(Cell((int)transform_.position_.x, (int)transform_.position_.z), prevCell));
            prevCell = { (int)transform_.position_.x, (int)transform_.position_.z };
        }
        break;
    case TRACKING_MODE :
        if (!((int)pPlayer->GetPosition().x == routeList.front().x &&
            (int)pPlayer->GetPosition().z == routeList.front().y))
        {
            //もし目的地にたどり着いたら
            if ((int)transform_.position_.x == routeList.front().x &&
                (int)transform_.position_.z == routeList.front().y)
            {
                prevCell = { routeList.front().x, routeList.front().y };
                //Astar法
                Cell cellPPos = { (int)pPlayer->GetPosition().x, (int)pPlayer->GetPosition().z };
                Cell cellEPos = { (int)transform_.position_.x,   (int)transform_.position_.z };

                routeList = pStage->AStar(cellEPos, cellPPos);

                //リストの先頭を削除
                routeList.pop_front();
            }
        }
        break;
    default:
        break;
    }

    XMFLOAT3 fMove = { routeList.front().x + 0.5f - transform_.position_.x, 0, routeList.front().y + 0.5f - transform_.position_.z };
    XMVECTOR vMove = XMLoadFloat3(&fMove);
    vMove = XMVector3Normalize(vMove);
    vMove *= SPEED;
    XMStoreFloat3(&fMove, vMove);
    transform_.position_ = Transform::Float3Add(transform_.position_, fMove);

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

    //敵から自分のベクトルを作る
    XMFLOAT3 pPos = pPlayer->GetPosition();
    XMVECTOR vEPos = XMLoadFloat3(&transform_.position_);
    XMVECTOR vPPos = XMLoadFloat3(&pPos);
    XMVECTOR vEnemyFromPlayer = vPPos - vEPos;
    XMVECTOR nEnemyFromPlayer = XMVector3Normalize(vEnemyFromPlayer);
    
    //視線ベクトルを作る
    XMVECTOR eRayVec = { 0, 0, 1, 0 };
    XMMATRIX mY = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y)); 
    eRayVec = XMVector3Normalize(XMVector3TransformCoord(eRayVec, mY));

    //敵から自分のベクトルと視線ベクトルの内積をとって視界に入っているか調べる
    float viewDot = XMVectorGetX(XMVector3Dot(vEnemyFromPlayer, eRayVec));

    //視界に入っていて（壁は無視する）距離が近ければ
    if (viewDot > VIEWING_ANGLE && XMVectorGetX(XMVector3Length(vEnemyFromPlayer)) < NEAR_DISTANCE)
    {
        //モードチェンジ
        mode = TRACKING_MODE;
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
void Akabei::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//開放
void Akabei::Release()
{
}

void Akabei::Astar()
{

}


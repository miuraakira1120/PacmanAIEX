#include "Aosuke.h"
#include "Engine/Model.h"
#include "Engine/SphereCollider.h"
#include <queue>
#include "Player.h"
#include "Akabei.h"

//�R���X�g���N�^
Aosuke::Aosuke(GameObject* parent)
    :GameObject(parent, "Aobei"), hModel_(-1), mode(TERRITORIAL_MODE), prevCell(-1, -1)
{
}

//�f�X�g���N�^
Aosuke::~Aosuke()
{
}

//������
void Aosuke::Initialize()
{
    transform_.position_.x = 11.5f;
    transform_.position_.z = 11.5f;

    //���f���f�[�^�̃��[�h
    hModel_ = Model::Load("aosuke.fbx");
    assert(hModel_ >= 0);

    pStage = (Stage*)FindObject("Stage");
    assert(pStage != nullptr);

    pPlayer = (Player*)FindObject("Player");
    assert(pPlayer != nullptr);

    pAkabei = (Akabei*)FindObject("Akabei");
    assert(pAkabei != nullptr);

    Cell cellPPos = { (int)pPlayer->GetPosition().x, (int)pPlayer->GetPosition().z };
    Cell cellEPos = { (int)transform_.position_.x, (int)transform_.position_.z };
    routeList = pStage->AStar(cellEPos, cellPPos);


    //���X�g�̐擪���폜
    routeList.pop_front();

    SphereCollider* collision = new SphereCollider(XMFLOAT3(0, 0, 0), 0.3f);
    AddCollider(collision);
}

//�X�V
void Aosuke::Update()
{
    XMVECTOR vPosition = XMLoadFloat3(&transform_.position_);
    XMVECTOR prevPosition = vPosition;

    XMFLOAT3 fAkabeiPos = pAkabei->GetPosition();
    XMVECTOR vAkabeiPos = XMLoadFloat3(&fAkabeiPos);

    XMVECTOR v = (vAkabeiPos - vPosition) * -1;
    XMStoreFloat3(&fAkabeiPos, v);
    bool flag = pStage->IsWall((int)fAkabeiPos.x, (int)fAkabeiPos.z);

    //mode = TRACKING_MODE;
    switch (mode)
    {
    case TRACKING_MODE:
        //�����ړI�n�ɂ��ǂ蒅������
        if ((int)transform_.position_.x == routeList.front().x &&
            (int)transform_.position_.z == routeList.front().y)
        {
            routeList.clear();
            routeList.push_front(pStage->RandEdgesCell(Cell((int)transform_.position_.x, (int)transform_.position_.z), prevCell));
            prevCell = { (int)transform_.position_.x, (int)transform_.position_.z };
        }
        break;
    case TERRITORIAL_MODE:
        if (!((int)pPlayer->GetPosition().x == routeList.front().x &&
            (int)pPlayer->GetPosition().z == routeList.front().y))
        {
            //�����ړI�n�ɂ��ǂ蒅������
            if ((int)transform_.position_.x == routeList.front().x &&
                (int)transform_.position_.z == routeList.front().y)
            {

                if (flag)
                {
                    prevCell = { routeList.front().x, routeList.front().y };
                    //Astar�@
                    Cell cellPPos = { (int)pPlayer->GetPosition().x, (int)pPlayer->GetPosition().z };
                    Cell cellEPos = { (int)transform_.position_.x,   (int)transform_.position_.z };

                    routeList = pStage->AStar(cellEPos, cellPPos);

                    //���X�g�̐擪���폜
                    routeList.pop_front();
                }
                else
                {
                    routeList.clear();
                    routeList.push_front(pStage->RandEdgesCell(Cell((int)transform_.position_.x, (int)transform_.position_.z), prevCell));
                    prevCell = { (int)transform_.position_.x, (int)transform_.position_.z };
                }
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

    //���݂̈ʒu�x�N�g��
    XMVECTOR nowPosition = XMLoadFloat3(&transform_.position_);

    //�ړ��x�N�g�������߂�
    XMVECTOR move = nowPosition - prevPosition;

    //�ړ��x�N�g���̒����𑪂�
    XMVECTOR lenght = XMVector3Length(move);
    //0.1�ȏ�ړ����Ă������]����
    if (XMVectorGetY(lenght) > 0.1)
    {
        //�x�N�g���𐳋K������
        move = XMVector3Normalize(move);

        //��ƂȂ鉜�s���̃x�N�g��
        XMVECTOR front = { 0,0,1,0 };

        //front��move�̓��ς����߂�
        XMVECTOR vecDot = XMVector3Dot(front, move);
        float dot = XMVectorGetY(vecDot);

        //�����Ă���p�x�����߂�
        float angle = acos(dot);

        //front��move�̊O�ς����߂�
        XMVECTOR cross = XMVector3Cross(front, move);

        //�O�ς̌��ʂ�Y���}�C�i�X�@���@�������@���@���ɐi��ł���
        if (XMVectorGetY(cross) < 0)
        {
            angle *= -1;
        }

        //���̂Ԃ��]������
        transform_.rotate_.y = angle * (180.0f / 3.14f);
    }

    //�G���玩���̃x�N�g�������
    XMFLOAT3 pPos = pPlayer->GetPosition();
    XMVECTOR vEPos = XMLoadFloat3(&transform_.position_);
    XMVECTOR vPPos = XMLoadFloat3(&pPos);
    XMVECTOR vEnemyFromPlayer = vPPos - vEPos;
    XMVECTOR nEnemyFromPlayer = XMVector3Normalize(vEnemyFromPlayer);

    //�����x�N�g�������
    XMVECTOR eRayVec = { 0, 0, 1, 0 };
    XMMATRIX mY = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));
    eRayVec = XMVector3Normalize(XMVector3TransformCoord(eRayVec, mY));

    //�G���玩���̃x�N�g���Ǝ����x�N�g���̓��ς��Ƃ��Ď��E�ɓ����Ă��邩���ׂ�
    float viewDot = XMVectorGetX(XMVector3Dot(vEnemyFromPlayer, eRayVec));

    //���E�ɓ����Ă��āi�ǂ͖�������j�������߂����
    if (viewDot > VIEWING_ANGLE && XMVectorGetX(XMVector3Length(vEnemyFromPlayer)) < NEAR_DISTANCE)
    {
        //���[�h�`�F���W
        mode = TRACKING_MODE;
    }

    /////////�Փ˔���////////////

    //�ǂƂ̏Փ˔���
    int checkX, checkZ;

    //�E
    checkX = (int)(transform_.position_.x + 0.3f);
    checkZ = (int)(transform_.position_.z);

    if (pStage->IsWall(checkX, checkZ))
    {
        transform_.position_.x = (float)((int)(transform_.position_.x + 0.5f) - 0.3f);

    }
    //��
    checkX = (int)(transform_.position_.x - 0.3f);
    if (pStage->IsWall(checkX, checkZ))
    {
        transform_.position_.x = (float)((int)(transform_.position_.x + 0.5) + 0.3f);

    }
    //��
    checkX = (int)(transform_.position_.x);
    checkZ = (int)(transform_.position_.z - 0.3f);
    if (pStage->IsWall(checkX, checkZ))
    {
        transform_.position_.z = (float)((int)(transform_.position_.z + 0.5) + 0.3f);

    }

    //��
    checkZ = (int)(transform_.position_.z + 0.3f);
    if (pStage->IsWall(checkX, checkZ))
    {
        transform_.position_.z = (float)((int)(transform_.position_.z + 0.5f) - 0.3f);
    }
}

//�`��
void Aosuke::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//�J��
void Aosuke::Release()
{
}
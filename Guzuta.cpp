#include "Guzuta.h"
#include "Engine/Model.h"
#include "Engine/SphereCollider.h"

//�R���X�g���N�^
Guzuta::Guzuta(GameObject* parent)
    :GameObject(parent, "Guzuta"), hModel_(-1)
{
}

//�f�X�g���N�^
Guzuta::~Guzuta()
{
}

//������
void Guzuta::Initialize()
{
    //���f���f�[�^�̃��[�h
    hModel_ = Model::Load("guzuta.fbx");
    assert(hModel_ >= 0);

    pStage = (Stage*)FindObject("Stage");
    assert(pStage != nullptr);

    transform_.position_.x = 10.5;
    transform_.position_.z = 12.5;

    SphereCollider* collision = new SphereCollider(XMFLOAT3(0, 0, 0), 0.3f);
    AddCollider(collision);
}

//�X�V
void Guzuta::Update()
{
    //transform_.position_.x += 0.1;
    XMVECTOR prevPosition = XMLoadFloat3(&transform_.position_);

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
void Guzuta::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//�J��
void Guzuta::Release()
{
}

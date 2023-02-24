#pragma once
#include "Engine/GameObject.h"
#include "Stage.h"

static const std::pair<int, int> DIRECCIONS[] = {
    { -1, 0 },
    { +1, 0 },
    { 0, -1 },
    { 0, +1 }
};

static enum Move
{
    UP_ROW = 0,
    DOWN_ROW,
    LEFT_COL,
    RIGHT_COL,
};

//���������Ǘ�����N���X
class Akabei : public GameObject
{
    int hModel_;    //���f���ԍ�

    Stage* pStage = nullptr;

public:
    //�R���X�g���N�^
    Akabei(GameObject* parent);

    //�f�X�g���N�^
    ~Akabei();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;

    //Astar�@�ł̒T��
    void Astar();

};

#pragma once
#include "Engine/GameObject.h"
#include "Stage.h"

//���������Ǘ�����N���X
class Aosuke : public GameObject
{
    int hModel_;    //���f���ԍ�

    Stage* pStage = nullptr;

    std::pair<int, int> Map_Start;
    std::pair<int, int> MAP_GOAL;

public:
    //�R���X�g���N�^
    Aosuke(GameObject* parent);

    //�f�X�g���N�^
    ~Aosuke();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;
};

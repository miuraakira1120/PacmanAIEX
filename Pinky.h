#pragma once
#include "Engine/GameObject.h"
#include "Stage.h"

//���������Ǘ�����N���X
class Pinky : public GameObject
{
    int hModel_;    //���f���ԍ�

    Stage* pStage = nullptr;
public:
    //�R���X�g���N�^
    Pinky(GameObject* parent);

    //�f�X�g���N�^
    ~Pinky();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;
};

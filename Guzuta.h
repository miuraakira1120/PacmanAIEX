#pragma once
#include "Engine/GameObject.h"
#include "Stage.h"

//���������Ǘ�����N���X
class Guzuta : public GameObject
{
    int hModel_;    //���f���ԍ�

    Stage* pStage = nullptr;
public:
    //�R���X�g���N�^
    Guzuta(GameObject* parent);

    //�f�X�g���N�^
    ~Guzuta();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;
};

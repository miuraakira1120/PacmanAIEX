#pragma once

#include "Engine/GameObject.h"


//���������Ǘ�����N���X

class Wall : public GameObject

{
    int hModel_;    //���f���ԍ�

public:

    //�R���X�g���N�^

    Wall(GameObject* parent);


    //�f�X�g���N�^

    ~Wall();


    //������

    void Initialize() override;


    //�X�V

    void Update() override;


    //�`��

    void Draw() override;


    //�J��

    void Release() override;

};
#pragma once
#include "Engine/GameObject.h"
#include "Stage.h"

class Player;
class Akabei;

//���������Ǘ�����N���X
class Aosuke : public GameObject
{
    int hModel_;    //���f���ԍ�
    Stage* pStage = nullptr;
    Player* pPlayer = nullptr;
    Akabei* pAkabei = nullptr;
    std::list<Cell> routeList;
    int mode;
    Cell prevCell;

    const float VIEWING_ANGLE = 0.3f;//����p�i-1����1�j
    const float NEAR_DISTANCE = 4.0f;
    const float SPEED = 0.05f;

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

    //Astar�@�ł̒T��
    void Astar();

};

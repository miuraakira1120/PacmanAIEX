#pragma once
#include "Engine/GameObject.h"
#include "Stage.h"

class Player;

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

enum MODE
{
    TERRITORIAL_MODE = 0,
    TRACKING_MODE,
};

//���������Ǘ�����N���X
class Akabei : public GameObject
{
    int hModel_;    //���f���ԍ�
    Stage* pStage = nullptr;
    Player* pPlayer = nullptr;
    std::list<Cell> routeList;
    int mode;
    Cell prevCell;

    const float VIEWING_ANGLE = 0.3f;//����p�i-1����1�j
    const float NEAR_DISTANCE = 7.0f;

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

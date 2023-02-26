#pragma once

#include "Engine/GameObject.h"
#include <vector>

class Node;

static const int MAP_ROW = 23;
static const int MAP_COL = 23;
//vector<Node> Open;	//�v�Z���̃m�[�h���i�[���Ă������߂̗D��x�t���L���[
//vector<Node> Close;	//�v�Z�ς݂̃m�[�h���i�[���Ă���

using std::queue;
using std::vector;
using std::pair;

struct Cell
{
    int x = 0;
    int z = 0;
};

struct Node
{
    Cell position;
    vector<Cell> edges;	// �אڃm�[�h(��)
    float heuristicCost;	// �q���[���X�e�B�b�N�R�X�g
    float totalCost;	// �R�X�g(�q���[���X�e�B�b�N�R�X�g����)
};

//���������Ǘ�����N���X
class Stage : public GameObject
{
    
    int hModel_[2];    //���f���ԍ�
    int map_[MAP_ROW][MAP_COL];

    Node nodeMap[MAP_ROW][MAP_COL];
    
public:

    //�R���X�g���N�^

    Stage(GameObject* parent);


    //�f�X�g���N�^

    ~Stage();


    //������

    void Initialize() override;


    //�X�V

    void Update() override;


    //�`��

    void Draw() override;


    //�J��

    void Release() override;

    //�����͕ǂ��ǂ���
    bool IsWall(int x, int z);

    //void InitNodeMap();

    //bool AstarSub(pair<int, int> startCel_, pair<int, int> goalCel_, int openNode_);

    //void Astar(pair<int, int> startCel_, pair<int, int> goalCel_);

    //Node�̍쐬
    void InitNode();

    bool IsCellWithinTheRange();

    /// <summary>
    /// �R�X�g�̏�����
    /// </summary>
    void InitCost();

    void AStar(Cell start, Cell goal);
};
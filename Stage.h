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

#include<iostream>
#include<queue>
#include<Windows.h>
#include <iomanip>
#include <algorithm>
#include <vector>

using std::queue;
using std::vector;
using std::pair;

struct Cell
{
    Cell() :
        x(-1),
        y(-1)
    {
    }

    Cell(int X, int Y)
    {
        x = X;
        y = Y;
    }

    int x;		//�s
    int y;		//��
};

struct Node
{
    Cell position;
    std::vector<Node*> edges;	// �אڃm�[�h(��)
    float heuristicCost;	// �q���[���X�e�B�b�N�R�X�g
    float totalCost;	// �R�X�g(�q���[���X�e�B�b�N�R�X�g����)
};

// �폜����
enum EraseResult
{
    NotFound,		// ������
    Erased,			// �폜
    CouldntErased	// �폜�ł��Ȃ�
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

    // �Z���͈̔͂��`�F�b�N����֐�
    bool IsCellWithinTheRange(int x, int y);

    /// <summary>
    /// �R�X�g�̏�����
    /// </summary>
    void InitCost();

    void AStar(Cell start, Cell goal);

    bool Less(Node* a, Node* b);
};
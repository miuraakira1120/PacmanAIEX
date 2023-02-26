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
//#include<iostream>
//#include<queue>
//#include<Windows.h>
//#include <iomanip>
//#include <algorithm>
//
//#include "Stage.h"
//
//
//using std::queue;
//using std::vector;
//using std::cout;
//using std::pair;
//using std::setw;
//
//const std::pair<int, int> MAP_START = { 2, 1 };	//�X�^�[�g���W
//const std::pair<int, int> MAP_GOAL = { 5, 10 };	//�S�[���̍��W
//
////�z��0 UP
////�z��1 DOWN
////�z��2 LEFT
////�z��3 RIGHT
////first ROW
////seco  COL
//const std::pair<int, int> DIRECCIONS[] = {
//	{ -1, 0 },
//	{ +1, 0 },
//	{ 0, -1 },
//	{ 0, +1 }
//};
//
//enum Move
//{
//	UP_ROW = 0,
//	DOWN_ROW,
//	LEFT_COL,
//	RIGHT_COL,
//};
//
//class Node
//{
//private:
//	int row;//�c
//	int col;//��
//	int cost;//�ړ��R�X�g�A�Ⴏ��ΒႢ�قǂ���
//	int mapCost;//�}�b�v���Ƃ̈ړ��R�X�g
//	std::pair<int, int> parentNode = { -1, -1 };//�ǂ����痈����
//	bool isOpen = false;//open�o���邩�ǂ���
//	bool isRoad = false;//�����ǂ���
//
//
//public:
//	Node();
//	~Node();
//	void SetPos(int row_, int col_);
//	void SetCost(int cost_);
//	void SetMapCost(int cost_);
//	void SetIsOpen(bool flag_);
//	void SetParentNode(std::pair<int, int> parentNode_);
//	void SetIsRoad(bool flag_);
//	int GetRowPos();
//	int GetPosCol();
//	bool GetIsOpen();
//	pair<int, int> GetColRow();
//	int GetCost();
//	int GetMapCost();
//	std::pair<int, int> GetParentNode();
//	bool GetIsRoad();
//	int GoalDistance();
//	int StartDistance();
//	int MoveCost();
//};

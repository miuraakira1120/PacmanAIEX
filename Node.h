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
	vector<Cell> edges;	// 隣接ノード(辺)
	float heuristicCost;	// ヒューリスティックコスト
	float totalCost;	// コスト(ヒューリスティックコスト込み)
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
//const std::pair<int, int> MAP_START = { 2, 1 };	//スタート座標
//const std::pair<int, int> MAP_GOAL = { 5, 10 };	//ゴールの座標
//
////配列0 UP
////配列1 DOWN
////配列2 LEFT
////配列3 RIGHT
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
//	int row;//縦
//	int col;//横
//	int cost;//移動コスト、低ければ低いほどいい
//	int mapCost;//マップごとの移動コスト
//	std::pair<int, int> parentNode = { -1, -1 };//どこから来たか
//	bool isOpen = false;//open出来るかどうか
//	bool isRoad = false;//道かどうか
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

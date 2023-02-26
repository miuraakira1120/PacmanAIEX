//#include "Node.h"
//
//Node::Node()
//{
//}
//
//Node::~Node()
//{
//	row = -1;
//	col = -1;
//	cost = 9999;
//	mapCost = -1;
//}
//
//void Node::SetPos(int row_, int col_)
//{
//	row = row_;
//	col = col_;
//}
//
//void Node::SetCost(int cost_)
//{
//	cost = cost_;
//}
//
//void Node::SetMapCost(int mapCost_)
//{
//	mapCost = mapCost_;
//}
//
//void Node::SetIsOpen(bool flag)
//{
//	isOpen = flag;
//}
//
//void Node::SetParentNode(std::pair<int, int> parentNode_)
//{
//	parentNode = parentNode_;
//}
//
//void Node::SetIsRoad(bool flag_)
//{
//	isRoad = flag_;
//}
//
//int Node::GetRowPos()
//{
//	return row;
//}
//
//int Node::GetPosCol()
//{
//	return col;
//}
//
//bool Node::GetIsOpen()
//{
//	return isOpen;
//}
//
//pair<int, int> Node::GetColRow()
//{
//	return pair<int, int>(row, col);
//}
//
//int Node::GetCost()
//{
//	return cost;
//}
//
//int Node::GetMapCost()
//{
//	return mapCost;
//}
//
//std::pair<int, int> Node::GetParentNode()
//{
//	return parentNode;
//}
//
//bool Node::GetIsRoad()
//{
//	return isRoad;
//}
//
//int Node::GoalDistance()
//{
//	int row = abs(MAP_GOAL.first - this->row);
//	int col = abs(MAP_GOAL.second - this->col);
//	return row + col;
//}
//
//int Node::StartDistance()
//{
//	int row = abs(MAP_START.first - this->row);
//	int col = abs(MAP_START.second - this->col);
//	return row + col;
//}
//
//int Node::MoveCost()
//{
//	return GoalDistance() + StartDistance();

#include "Node.h"

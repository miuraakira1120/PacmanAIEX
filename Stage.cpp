#include "Stage.h"
#include "Engine/Model.h"
#include "Engine/CsvReader.h"
#include "Node.h"


//コンストラクタ
Stage::Stage(GameObject* parent)
    :GameObject(parent, "Stage"), hModel_{-1,-1}
{
}

//デストラクタ
Stage::~Stage()
{
}

//初期化
void Stage::Initialize()
{
    //モデルデータのロード
    hModel_ [0]= Model::Load("floor.fbx");
    assert(hModel_ >= 0);
    hModel_[1] = Model::Load("Wall.fbx");
    assert(hModel_ >= 0);

    CsvReader csv;
    csv.Load("PacMap.csv");

    for (int i = 0; i < MAP_ROW; i++)
    {
        for (int j = 0; j < MAP_COL; j++)
        {
            map_[i][MAP_COL - 1 - j] = csv.GetValue(i, j);
        }
    }

    //InitNodeMap();
}

//更新
void Stage::Update()
{
}

//描画
void Stage::Draw()
{
    for (int x = 0; x < MAP_ROW ; x++)
    {
        for (int z = 0; z < MAP_COL; z++)
        {
            int type = map_[x][z];
            transform_.position_.x = x;
            transform_.position_.z = z;
            Model::SetTransform(hModel_[type], transform_);
            Model::Draw(hModel_[type]);
        }       
    }         
}

//開放
void Stage::Release()
{
}

//壁かどうか
bool Stage::IsWall(int x, int z)
{
    return map_[x][z] == 1;
}
/*

void Stage::InitNodeMap()
{
    for (int i = 0; i < MAP_ROW; i++)
    {
        for (int j = 0; j < MAP_COL; j++)
        {
            nodeMap[i][j].SetMapCost(map_[i][j]);
            nodeMap[i][j].SetPos(i, j);
        }
    }
}*/

//
//bool Stage::AstarSub(pair<int, int> startCel_, pair<int, int> goalCel_, int openNode_)
//{
//	Open.erase(std::cbegin(Open) + openNode_);
//	Node LowCostNode;
//	LowCostNode.SetCost(9999);
//	//Openリストに格納されているノードの内、最小のノードを1つ取り出す
//	for (const auto& dir : DIRECCIONS)
//	{
//		int nextRow = nodeMap[startCel_.first][startCel_.second].GetRowPos() + dir.first;
//		int nextCol = nodeMap[startCel_.first][startCel_.second].GetPosCol() + dir.second;
//
//		//次のノードの親ノードを設定
//		nodeMap[nextRow][nextCol].SetParentNode(startCel_);
//		std::pair<int, int> aaa = nodeMap[nextRow][nextCol].GetParentNode();
//
//		if (nodeMap[nextRow][nextCol].GetIsOpen() == false && nodeMap[nextRow][nextCol].GetMapCost() > -1)//openにもcloseにも障害物もダメ)
//		{
//			int nextCost = nodeMap[nextRow][nextCol].StartDistance() + nodeMap[nextRow][nextCol].GoalDistance();
//			nodeMap[nextRow][nextCol].SetCost(nextCost);
//
//			Open.push_back(nodeMap[nextRow][nextCol]);
//			nodeMap[nextRow][nextCol].SetIsOpen(true);
//
//
//			//コストの少ない
//			if (nodeMap[nextRow][nextCol].GetCost() < LowCostNode.GetCost())
//			{
//				LowCostNode.SetCost(nodeMap[nextRow][nextCol].GetCost());
//				LowCostNode.SetPos(nodeMap[nextRow][nextCol].GetRowPos(), nodeMap[nextRow][nextCol].GetPosCol());
//
//			}
//		}
//	}
//	//もしゴールノードだったら
//	if (goalCel_.first == LowCostNode.GetRowPos() && goalCel_.second == LowCostNode.GetPosCol())
//	{
//		return true;
//	}
//	return false;
//}
//
//void Stage::Astar(pair<int, int> startCel_, pair<int, int> goalCel_)
//{
//	int endFlag = false;
//	Open.push_back(nodeMap[startCel_.first][startCel_.second]);
//	nodeMap[startCel_.first][startCel_.second].SetIsOpen(true);
//	//Closeキューの初期化
//	/*for (int i = 0; i < Close.size(); i++)
//	{
//		Close.pop();
//	}*/
//
//	//Openリストが空なら探索は失敗
//	while (Open.size() != 0 && endFlag == false)
//	{
//		int minCost = 9999;
//		int min = 0;
//		for (int i = 0; i < Open.size() - 1; i++)
//		{
//			if (minCost > Open[i].GetCost())
//			{
//				minCost = Open[i].GetCost();
//				min = i;
//			}
//		}
//
//		Node tmp = Open[min];
//		Close.push_back(tmp);
//		endFlag = AstarSub(Open[min].GetColRow(), goalCel_, min);
//	}
//
//	std::pair<int, int> next = { -1, -1 };
//
//	//vector<std::pair<int, int>> mol;
//	//mol.push_back(nodeMap[goalCel_.first][goalCel_.second].GetParentNode());
//	next = nodeMap[goalCel_.first][goalCel_.second].GetParentNode();
//	while (!nodeMap[next.first][next.second].GetParentNode().first == -1)
//	{
//		//mol.push_back(nodeMap[next.first][next.second].GetParentNode());
//		nodeMap[next.first][next.second].SetIsRoad(true);
//		next = nodeMap[next.first][next.second].GetParentNode();
//	}
//}


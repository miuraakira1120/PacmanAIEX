#include "Stage.h"
#include "Engine/Model.h"
#include "Engine/CsvReader.h"

#include<iostream>
#include<queue>
#include<Windows.h>
#include <iomanip>
#include <algorithm>
#include <vector>

#include <stdio.h>
#include <memory.h>
#include <list>
#include <math.h>

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

    InitNode();
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

//ノードを生成
void Stage::InitNode()
{
    for (int x = 0; x < MAP_ROW; x++)
    {
        for (int y = 0; y < MAP_COL; y++)
        {
            nodeMap[x][y].position.x = x;
            nodeMap[x][y].position.y = y;

            Cell cellDown  = { x, y - 1 };
            Cell cellLeft  = { x - 1, y };
            Cell cellRight = { x + 1, y };
            Cell cellUP    = { x, y + 1 };

            Cell adjacent_cells[] =
            {
                cellDown,
                cellLeft,
                cellRight,
                cellUP,
            };

            // 隣接ノードの追加
            for (const Cell& cell : adjacent_cells)
            {
                if (IsCellWithinTheRange(cell.x, cell.y) == true && map_[cell.x][cell.y] == 0)
                {
                    nodeMap[x][y].edges.push_back(&nodeMap[cell.x][cell.y]);
                }
            }
        }
    }
    int a = 0;
}
bool Stage::IsCellWithinTheRange(int x, int y)
{
    if (x >= 0 && x < MAP_ROW && y >= 0 && y < MAP_COL)
    {
        return true;
    }
    return false;
}

// コスト初期化
void Stage::InitCost()
{
    for (int x = 0; x < MAP_ROW; x++)
    {
        for (int y = 0; y < MAP_COL; y++)
        {
            nodeMap[x][y].heuristicCost = 9999;
            nodeMap[x][y].totalCost = 0;
        }
    }
}

//Nodeのソート関数(昇順)
bool Stage::Less(Node* a, Node* b)
{
    if (a->totalCost < b->totalCost)
    {
        return true;
    }

    return false;
}

// ノードとゴールまでの距離
float Stage::CalculateHeuristic(const Node* node, const Node* goal)
{
    float x = fabsf(goal->position.x - node->position.x);
    float y = fabsf(goal->position.y - node->position.y);

    return sqrtf(x * x + y * y);
}

//ランダムに行ける隣のマスを返す（戻りはしない）
Cell Stage::RandEdgesCell(Cell nowPos, Cell prevPos)
{
    vector<Cell> edgesCanMove;

    for (auto i : nodeMap[nowPos.x][nowPos.y].edges)
    {
        if (!((*i).position.x == prevPos.x && (*i).position.y == prevPos.y))
        {
            edgesCanMove.push_back((*i).position);
        }
    }

    if (edgesCanMove.size() < 0)
    {
        return Cell(-1, -1);
    }
    else
    {
        return edgesCanMove[rand() % edgesCanMove.size()];
    }
}

// セル比較
bool Stage::IsEqualCell(const Cell& a, const Cell& b)
{
    if (a.x == b.x && a.y == b.y)
    {
        return true;
    }

    return false;
}

EraseResult Stage::EraseNode(std::list<Node*>& list, Node* new_node, float new_cost)
{
    // クローズリストチェック
    for (auto itr = list.begin(); itr != list.end(); itr++)
    {
        // ノードと同じセルがあるか調べる
        if (IsEqualCell(new_node->position, (*itr)->position) == true)
        {
            // コストの比較
            if (new_cost < (*itr)->totalCost)
            {
                list.erase(itr);
                return EraseResult::Erased;
            }
            else
            {
                return EraseResult::CouldntErased;
            }
        }
    }
    return EraseResult::NotFound;
}

// オープンリストに追加
bool Stage::AddAdjacentNode(std::list<Node*>& open_list, std::list<Node*>& close_list, Node* adjacent_node, float cost)
{
    bool can_update = true;

    std::list<Node*> node_list[] =
    {
        close_list,
        open_list
    };

    for (std::list<Node*>& list : node_list)
    {
        // リストに同じノードがあってリストの方のコストが高いなら削除
        if (EraseNode(list, adjacent_node, cost) == EraseResult::CouldntErased)
        {
            can_update = false;
        }
    }

    if (can_update == true)
    {
        open_list.push_back(adjacent_node);
        return true;
    }

    return false;
}

std::list<Cell> Stage::AStar(Cell start, Cell goal)
{
    std::list<Node*> open_list;
    std::list<Node*> close_list;

    //const Node* start_node = &Map[start.Y][start.X];
    const Node* goal_node = &nodeMap[goal.x][goal.y];

    // 更新したノード位置保存用
    Cell last_update_cells[MAP_ROW][MAP_COL];

    // グラフの初期化
    InitCost();

    // スタートノードの指定
    open_list.push_back(&nodeMap[start.x][start.y]);

    // 経路探索回数
    int count = 0;

    // オープンリストがなくなるまで回す
    while (open_list.empty() == false)
    {
        count++;

        Node* search_node = (*open_list.begin());
        // 探索リストから除外
        open_list.erase(open_list.begin());

        // ゴールに到達したら終わり
        if (IsEqualCell(search_node->position, goal) == true)
        {
            // クローズリストに最後のノードを追加する
            close_list.push_back(search_node);
            break;
        }

        for (Node* adjacent_node : search_node->edges)
        {
            // 計算を行っていなかった場合だけ計算
            if (adjacent_node->heuristicCost == 9999)
            {
                // ヒューリスティクスコスト計算
                adjacent_node->heuristicCost = CalculateHeuristic(adjacent_node, goal_node);
            }

            // ノード間コスト
            float edge_cost = map_[adjacent_node->position.x][adjacent_node->position.y];
            // 取得ノードのトータルコスト
            float node_cost = search_node->totalCost;
            //トータルコスト算出
            float total_cost = edge_cost + adjacent_node->heuristicCost + node_cost;

            // ノード追加
            if (AddAdjacentNode(open_list, close_list, adjacent_node, total_cost))
            {
                // トータルコストを更新
                adjacent_node->totalCost = total_cost;

                if (adjacent_node->position.x == 0 && adjacent_node->position.y == 2)
                {
                    int xx = 0;
                    xx = 100;
                }

                // 経路を更新したセルを保存
                last_update_cells[adjacent_node->position.x][adjacent_node->position.y] = search_node->position;
            }
        }

        bool is_add_close = true;

        // クローズリストチェック
        for (auto itr = close_list.begin(); itr != close_list.end(); itr++)
        {
            // ノードと同じセルがあるか調べる
            if (IsEqualCell(search_node->position, (*itr)->position) == true)
            {
                is_add_close = false;
                break;
            }
        }

        // 同じノードが無かったので追加
        if (is_add_close == true)
        {
            // このノードの探索終了
            close_list.push_back(search_node);
        }

        // 昇順ソート
        open_list.sort();
        /*for (int i = 0; i < open_list.size() - 2; i++)
        {
            open_list
        }*/
    }

    // 経路復元
    std::list<Cell> lRoute;

    // ゴールセルから復元する
    lRoute.push_back(goal);
    while (lRoute.empty() == false)
    {
        Cell route = lRoute.front();

        // スタートセルなら終了
        if (IsEqualCell(route, start) == true)
        {
            //lRouteの中身が確定
            break;
        }
        else
        {
            if (IsCellWithinTheRange(route.x, route.y) == true)
            {
                // 追加
                lRoute.push_front(last_update_cells[route.x][route.y]);
            }
            else
            {
                //経路が見つからなかったとき
                //うーんどうしよ
                break;
            }
        }
    }
    return lRoute;
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


#pragma once

#include "Engine/GameObject.h"
#include <vector>

class Node;

static const int MAP_ROW = 23;
static const int MAP_COL = 23;
//vector<Node> Open;	//計算中のノードを格納しておくための優先度付きキュー
//vector<Node> Close;	//計算済みのノードを格納しておく

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

    int x;		//行
    int y;		//列
};

struct Node
{
    Cell position;
    std::vector<Node*> edges;	// 隣接ノード(辺)
    float heuristicCost;	// ヒューリスティックコスト
    float totalCost;	// コスト(ヒューリスティックコスト込み)
};

// 削除結果
enum EraseResult
{
    NotFound,		// 未発見
    Erased,			// 削除
    CouldntErased	// 削除できない
};

//◆◆◆を管理するクラス
class Stage : public GameObject
{
    
    int hModel_[2];    //モデル番号
    int map_[MAP_ROW][MAP_COL];

    Node nodeMap[MAP_ROW][MAP_COL];
    
public:

    //コンストラクタ

    Stage(GameObject* parent);


    //デストラクタ

    ~Stage();


    //初期化

    void Initialize() override;


    //更新

    void Update() override;


    //描画

    void Draw() override;


    //開放

    void Release() override;

    //そこは壁かどうか
    bool IsWall(int x, int z);

    //void InitNodeMap();

    //bool AstarSub(pair<int, int> startCel_, pair<int, int> goalCel_, int openNode_);

    //void Astar(pair<int, int> startCel_, pair<int, int> goalCel_);

    //Nodeの作成
    void InitNode();

    // セルの範囲をチェックする関数
    bool IsCellWithinTheRange(int x, int y);

    /// <summary>
    /// コストの初期化
    /// </summary>
    void InitCost();

    void AStar(Cell start, Cell goal);

    bool Less(Node* a, Node* b);
};
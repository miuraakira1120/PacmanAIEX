#pragma once

#include "Engine/GameObject.h"
#include <vector>

class Node;

static const int MAP_ROW = 23;
static const int MAP_COL = 23;
//vector<Node> Open;	//計算中のノードを格納しておくための優先度付きキュー
//vector<Node> Close;	//計算済みのノードを格納しておく

//◆◆◆を管理するクラス
class Stage : public GameObject
{
    
    int hModel_[2];    //モデル番号
    int map_[MAP_ROW][MAP_COL];

    //Node nodeMap[MAP_ROW][MAP_COL];
    
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

};
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

//�R���X�g���N�^
Stage::Stage(GameObject* parent)
    :GameObject(parent, "Stage"), hModel_{-1,-1}
{
}

//�f�X�g���N�^
Stage::~Stage()
{
}

//������
void Stage::Initialize()
{
    //���f���f�[�^�̃��[�h
    hModel_ [0]= Model::Load("floor.fbx");
    assert(hModel_ >= 0);
    hModel_[1] = Model::Load("Wall.fbx");
    assert(hModel_ >= 0);

    CsvReader csv;
    csv.Load("PacMap2.csv");

    for (int i = 0; i < MAP_ROW; i++)
    {
        for (int j = 0; j < MAP_COL; j++)
        {
            map_[i][MAP_COL - 1 - j] = csv.GetValue(i, j);
        }
    }

    InitNode();
}

//�X�V
void Stage::Update()
{
}

//�`��
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

//�J��
void Stage::Release()
{
}

//�ǂ��ǂ���
bool Stage::IsWall(int x, int z)
{
    return map_[x][z] == 1;
}

//�m�[�h�𐶐�
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

            // �אڃm�[�h�̒ǉ�
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

// �R�X�g������
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

// �m�[�h�ƃS�[���܂ł̋���
float Stage::CalculateHeuristic(const Node* node, const Node* goal)
{
    float x = fabsf(goal->position.x - node->position.x);
    float y = fabsf(goal->position.y - node->position.y);

    return sqrtf(x * x + y * y);
}

//�����_���ɍs����ׂ̃}�X��Ԃ��i�߂�͂��Ȃ��j
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

// �Z����r
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
    // �N���[�Y���X�g�`�F�b�N
    for (auto itr = list.begin(); itr != list.end(); itr++)
    {
        // �m�[�h�Ɠ����Z�������邩���ׂ�
        if (IsEqualCell(new_node->position, (*itr)->position) == true)
        {
            // �R�X�g�̔�r
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

// �I�[�v�����X�g�ɒǉ�
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
        // ���X�g�ɓ����m�[�h�������ă��X�g�̕��̃R�X�g�������Ȃ�폜
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

    // �X�V�����m�[�h�ʒu�ۑ��p
    Cell last_update_cells[MAP_ROW][MAP_COL];

    // �O���t�̏�����
    InitCost();

    // �X�^�[�g�m�[�h�̎w��
    open_list.push_back(&nodeMap[start.x][start.y]);

    // �I�[�v�����X�g���Ȃ��Ȃ�܂ŉ�
    while (open_list.empty() == false)
    {
        Node* search_node = (*open_list.begin());
        // �T�����X�g���珜�O
        open_list.erase(open_list.begin());

        // �S�[���ɓ��B������I���
        if (IsEqualCell(search_node->position, goal) == true)
        {
            // �N���[�Y���X�g�ɍŌ�̃m�[�h��ǉ�����
            close_list.push_back(search_node);
            break;
        }

        for (Node* adjacent_node : search_node->edges)
        {
            // �v�Z���s���Ă��Ȃ������ꍇ�����v�Z
            if (adjacent_node->heuristicCost == 9999)
            {
                // �q���[���X�e�B�N�X�R�X�g�v�Z
                adjacent_node->heuristicCost = CalculateHeuristic(adjacent_node, goal_node);
            }

            // �m�[�h�ԃR�X�g
            float edge_cost = map_[adjacent_node->position.x][adjacent_node->position.y];
            // �擾�m�[�h�̃g�[�^���R�X�g
            float node_cost = search_node->totalCost;
            //�g�[�^���R�X�g�Z�o
            float total_cost = edge_cost + adjacent_node->heuristicCost + node_cost;

            // �m�[�h�ǉ�
            if (AddAdjacentNode(open_list, close_list, adjacent_node, total_cost))
            {
                // �g�[�^���R�X�g���X�V
                adjacent_node->totalCost = total_cost;

                if (adjacent_node->position.x == 0 && adjacent_node->position.y == 2)
                {
                    int xx = 0;
                    xx = 100;
                }

                // �o�H���X�V�����Z����ۑ�
                last_update_cells[adjacent_node->position.x][adjacent_node->position.y] = search_node->position;
            }
        }

        bool is_add_close = true;

        // �N���[�Y���X�g�`�F�b�N
        for (auto itr = close_list.begin(); itr != close_list.end(); itr++)
        {
            // �m�[�h�Ɠ����Z�������邩���ׂ�
            if (IsEqualCell(search_node->position, (*itr)->position) == true)
            {
                is_add_close = false;
                break;
            }
        }

        // �����m�[�h�����������̂Œǉ�
        if (is_add_close == true)
        {
            // ���̃m�[�h�̒T���I��
            close_list.push_back(search_node);
        }

        // �����\�[�g
        open_list.sort();
        /*for (int i = 0; i < open_list.size() - 2; i++)
        {
            open_list
        }*/
    }

    // �o�H����
    std::list<Cell> lRoute;

    // �S�[���Z�����畜������
    lRoute.push_back(goal);
    while (lRoute.empty() == false)
    {
        Cell route = lRoute.front();

        // �X�^�[�g�Z���Ȃ�I��
        if (IsEqualCell(route, start) == true)
        {
            //lRoute�̒��g���m��
            break;
        }
        else
        {
            if (IsCellWithinTheRange(route.x, route.y) == true)
            {
                // �ǉ�
                lRoute.push_front(last_update_cells[route.x][route.y]);
            }
            else
            {
                //�o�H��������Ȃ������Ƃ�
                //���[��ǂ�����
                break;
            }
        }
    }
    return lRoute;
}
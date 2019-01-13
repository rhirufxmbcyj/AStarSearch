#include "AStar.h"
#include <assert.h>
#include <algorithm>
using std::sort;

vector<a_node*> open_list;
int insert_neighbor_to_openlist(a_node *curr_node, a_node *_end, a_node _map[MAP_ROW][MAP_COLUMN])
{
    a_node *tmp = NULL;
    vector<a_node*>::iterator is_contain;
    //ȡ����ǰ�ڵ���������ҽڵ����open�б� ��������Щ�ڵ��parentΪ��ǰ�ڵ�
    //����ϵ�������±�������ͬ
    //��
    if (curr_node->x > 0)
    {
        tmp = &_map[curr_node->x-1][curr_node->y];
        is_contain = std::find(open_list.begin(), open_list.end(), tmp);
        if (tmp->attr != ATTR_FORBID && tmp->attr != ATTR_CLOSE && is_contain == open_list.end())
        {
            tmp->h = (abs(tmp->x - _end->x) + abs(tmp->y - _end->y))*STEP_LENGTH;
            tmp->g = curr_node->g + STEP_LENGTH;
            tmp->parent = curr_node;
            open_list.push_back(tmp);
        }
    }

    //��
    if (curr_node->x < MAP_ROW - 1)
    {
        tmp = &_map[curr_node->x+1][curr_node->y];
        is_contain = std::find(open_list.begin(), open_list.end(), tmp);
        if (tmp->attr != ATTR_FORBID && tmp->attr != ATTR_CLOSE && is_contain == open_list.end())
        {
            tmp->h = (abs(tmp->x - _end->x) + abs(tmp->y - _end->y))*STEP_LENGTH;
            tmp->g = curr_node->g + STEP_LENGTH;
            tmp->parent = curr_node;
            open_list.push_back(tmp);
        }
    }

    //��
    if (curr_node->y > 0)
    {
        tmp = &_map[curr_node->x][curr_node->y-1];
        is_contain = std::find(open_list.begin(), open_list.end(), tmp);
        if (tmp->attr != ATTR_FORBID && tmp->attr != ATTR_CLOSE && is_contain == open_list.end())
        {
            tmp->h = (abs(tmp->x - _end->x) + abs(tmp->y - _end->y))*STEP_LENGTH;
            tmp->g = curr_node->g + STEP_LENGTH;
            tmp->parent = curr_node;
            open_list.push_back(tmp);
        }
    }

    //��
    if (curr_node->y < MAP_COLUMN - 1)
    {
        tmp = &_map[curr_node->x][curr_node->y+1];
        is_contain = std::find(open_list.begin(), open_list.end(), tmp);
        if (tmp->attr != ATTR_FORBID && tmp->attr != ATTR_CLOSE && is_contain == open_list.end())
        {
            tmp->h = (abs(tmp->x - _end->x) + abs(tmp->y - _end->y))*STEP_LENGTH;
            tmp->g = curr_node->g + STEP_LENGTH;
            tmp->parent = curr_node;
            open_list.push_back(tmp);
        }
    }
    return 0;
}

bool comp_f(a_node *a, a_node *b)
{
    //�Ƚ�fֵ
    int a_f = a->g + a->h;
    int b_f = b->g + b->h;
    return a_f < b_f;
}

void find_destination(a_node *_start, a_node *_end, a_node _map[MAP_ROW][MAP_COLUMN])
{
    a_node *curr_node = NULL;
    if (_end->attr == ATTR_FORBID)
    {
        printf("destination is forbidden\n");
        return;
    }
    if (_start->x == _end->x && _start->y == _end->y)
    {
        printf("start = end\n");
        return;
    }
    //��������open�б�
    open_list.push_back(_start);
    do
    {
        //�õ�open�б���f��С�Ľڵ�
        curr_node = open_list.at(0);
        open_list.erase(open_list.begin());
        curr_node->attr = ATTR_CLOSE;
        if (curr_node->x < 0 || curr_node->x >= MAP_ROW || curr_node->y < 0 || curr_node->y >= MAP_COLUMN)
        {
            assert(0);
            break;
        }
        //printf("x=%d,y=%d\n", curr_node->x, curr_node->y);
        if (curr_node->x == _end->x && curr_node->y == _end->y)
        {
            printf("from %d,%d to %d,%d, find best way!\n",_start->x,_start->y,_end->x,_end->y);
            goto End;
        }

        //��ȡ�ڵ����ܿ��ƶ��Ľڵ㲢����open�б���
        insert_neighbor_to_openlist(curr_node, _end, _map);
        //����open�б� ��f��С�Ľڵ������ǰ��
        sort(open_list.begin(), open_list.end(), comp_f);

    } while (open_list.size() != 0);
    printf("can't find destination\n");
    return;
End:
    print_path(curr_node);
    print_map(_map);
}

void print_path(a_node *node)
{
    printf("print path backward order\n");
    while (node != NULL)
    {
        node->attr = ATTR_RIGHT;
        printf("%d,%d\n", node->x, node->y);
        node = node->parent;
    }
}

void print_map(a_node _map[MAP_ROW][MAP_COLUMN])
{
    printf("\n");
    for (int i = 0; i < MAP_ROW; i++)
    {
        for (int j = 0; j < MAP_COLUMN; j++)
        {
            if (_map[i][j].attr == ATTR_RIGHT)
                printf("* ");
            else if (_map[i][j].attr == ATTR_FORBID)
                printf("0 ");
            else
                printf("  ");
        }
        printf("\n");
    }
}


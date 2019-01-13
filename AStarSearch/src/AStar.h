#ifndef A_STAR_H
#define A_STAR_H

#include <iostream>
#include <vector>
using std::vector;
#include "define.h"

typedef struct a_node_t
{
    int x;
    int y;
    //������ƶ�����ǰ�ڵ�ĳ���
    int g;
    //��ǰ�ڵ㵽�յ�Ĺ��㳤��
    int h;
    //״̬
    int attr;
    struct a_node_t *parent;
}a_node;

void find_destination(a_node *_start,a_node *_end,a_node _map[MAP_ROW][MAP_COLUMN]);
int insert_neighbor_to_openlist(a_node *curr_node, a_node *_end, a_node _map[MAP_ROW][MAP_COLUMN]);
void print_path(a_node *node);
void print_map(a_node _map[MAP_ROW][MAP_COLUMN]);
bool comp_f(a_node *a, a_node *b);


#endif

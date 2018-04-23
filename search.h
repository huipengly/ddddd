#ifndef __SEARCH_H__
#define __SEARCH_H__

#include <vector>

struct request
{
    int number;                     //需求编号，可以考虑不要编号
    int request_band_width;         //需求带宽
    std::vector<std::vector<int>> route;   //备用线路
};

void search();
void make_map();
void print_map();
void make_request_vec();

#endif

#ifndef __SEARCH_H__
#define __SEARCH_H__

#include <vector>

struct request
{
    int number;                     //需求编号
    int request_band_width;         //需求带宽
    std::vector<std::vector<int>> route[3];   //备用线路
};

void search();
void make_map();

#endif

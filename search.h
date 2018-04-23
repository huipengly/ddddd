#ifndef __SEARCH_H__
#define __SEARCH_H__

#include <vector>

struct request
{
    int number;                     //需求编号，可以考虑不要编号
    int request_band_width;         //需求带宽
    std::vector<std::vector<int>> route;   //备用线路
};

struct Max_Percentage_Route
{
    double percentage;
    int start_node;
    int end_node;
};

void search();
void make_map();
void print_map_info(int map[500][500]);
void print_map_info(double map[500][500]);
void make_request_vec();
double calculate_max_percentage(Max_Percentage_Route &max_percentage_route);              //计算出使用率最大的
void calculate_each_route_usage();              //将每个要求的流量加入图里，计算出每段的使用量
void calculate_each_route_percentage();         //计算每段路的使用率
int rand_for_alternative_route();
void rand_choose();

#endif

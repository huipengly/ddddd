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
void print_map_info(int map[500][500]);
void print_map_info(double map[500][500]);
void make_request_vec();
double calculate_max_percentage();
void calculate_each_route_usage();
void calculate_each_route_percentage();
int rand_for_alternative_route();
void rand_choose();

#endif

#include "search.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <ctime>

using namespace std;

extern int grid_topo_data[956][3];
extern int request_data[4001][500];
int map[500][500] = {0};
int map_usage[500][500] ={0};
double map_percentage[500][500] ={0};
int request_choose[1000] = {0};

request request_vec[1000];

//你要完成的功能总入口
void search()
{
    std::srand(std::time(nullptr)); // 以当前时间为随机生成器的种子
    make_map();
//    print_map();

    make_request_vec();

//    for(int i = 0; i < 50*2000; ++i) {
//        calculate_max_percentage();
//        memset(map_usage,0, 500*500*sizeof(int) );
//    }
    double percentage = calculate_max_percentage();
    while( percentage > 0.31)
    {
        rand_choose();
        cout << percentage << endl;
        memset(map_usage,0, 500*500*sizeof(int) );
        percentage = calculate_max_percentage();
    }
    for (int i = 0; i < 1000; ++i) {
        cout << request_choose[i] << endl;
    }
    cout << percentage << endl;
//    print_map_info(map_percentage);
}

void make_map()
{
    for (int data_num = 1; data_num < 956; ++data_num)
    {
        //双向同时存储
        int row = grid_topo_data[data_num][0];
        int col = grid_topo_data[data_num][1];
        map[row][col] = grid_topo_data[data_num][2];
        map[col][row] = grid_topo_data[data_num][2];
    }
}

void print_map_info(int map[500][500])
{
    for (int  i= 0; i < 500; ++i)
    {
        for (int j = 0; j < 500; ++j)
        {
            cout << map[i][j] << '\t';
        }
        cout << endl;
    }
}

void print_map_info(double map[500][500])
{
    for (int  i= 0; i < 500; ++i)
    {
        for (int j = 0; j < 500; ++j)
        {
            cout << map[i][j] << '\t';
        }
        cout << endl;
    }
}

void make_request_vec()
{
    int line_counter = 1;    //记录读取行，忽略第一行
    while (line_counter < 4001)
    {
        int request_number = request_data[line_counter][0];                     //需求号
        int request_band_width = request_data[line_counter][1];                 //需求带宽
        request_vec[request_number].number = request_number;
        request_vec[request_number].request_band_width = request_band_width;

        //循环三个备选
        for(int back_counter = 0; back_counter < 3; ++back_counter)
        {
            vector<int> temp_route;
            int route_counter = 0;
            while ((request_data[line_counter + back_counter + 1][route_counter] > 0) || (route_counter < 5))//判断数值为0，且0不在前五个，为需求路线，添加。否则认为需求添加完成。
            {
                temp_route.push_back(request_data[line_counter + back_counter + 1][route_counter]);
                route_counter++;
            }
            request_vec[request_number].route.push_back(temp_route);            //添加一条备选的需求
        }
        line_counter = line_counter + 4;                                        //每4行为一个备选
    }
}

double calculate_max_percentage()
{
    calculate_each_route_percentage();
    return *max_element(&map_percentage[0][0], &map_percentage[499][499]);
}

void calculate_each_route_usage()
{
    for (request req : request_vec)
    {
        for (int i = 0; i < req.route[i].size() - 1; ++i)
        {
            map_usage[req.route[request_choose[i]][i]][req.route[request_choose[i]][i+1]] += req.request_band_width;
        }
    }
}

void calculate_each_route_percentage()
{
    calculate_each_route_usage();
    for (int i = 0; i < 500; ++i)
    {
        for (int j = 0; j < 500; ++j)
        {
            if(map[i][j] == 0)
            {
                map_percentage[i][j] = 0;
            }
            else {
                map_percentage[i][j] = 1.0 * map_usage[i][j] / map[i][j];
            }
        }
    }
}

int rand_for_alternative_route()
{
    return std::rand() / ((RAND_MAX + 1u) / 3);
}

void rand_choose()
{
    for (int& req : request_choose)
    {
        req = rand_for_alternative_route();
    }
}
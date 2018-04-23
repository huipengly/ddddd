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
Max_Percentage_Route max_percentage_route;

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
    double percentage = calculate_max_percentage(max_percentage_route);
    while( percentage > 0.5)
    {
        rand_choose();
        cout << percentage << endl;
        memset(map_usage,0, 500*500*sizeof(int) );
        percentage = calculate_max_percentage(max_percentage_route);
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

double calculate_max_percentage(Max_Percentage_Route &max_percentage_route)
{
    calculate_each_route_percentage();
    double *max = max_element(&map_percentage[0][0], &map_percentage[499][499]);
    int distance = (max - &map_percentage[0][0]);        //最大值距离0，0的距离。指针地址相减不需要再除类型大小例如sizeof(double)。
    max_percentage_route.percentage = *max;
    max_percentage_route.start_node = distance / 500;
    max_percentage_route.end_node = distance - max_percentage_route.start_node * 500;
    int col, row;
    for(int i = 0; i < 500; ++i)
    {
        for(int j = 0; j < 500; ++j)
        {
            if (fabs(map_percentage[i][j] - *max) < 1e-5)
            {
                col = i;
                row = j;
            }
        }
    }
    return *max;
}

void calculate_each_route_usage()
{
    for (int i = 0; i < 1000; ++i)                                      //每条需求的流量都要加入图
    {
        request req = request_vec[i];                                    //当前需求
        int request_choose_route = request_choose[i];                   //当前需求的备选线路
        for (int node = 0; node < req.route[request_choose_route].size() - 1; ++node)   //从需求的备选线路中循环节点，加到图的流量里，从点一个开始，到倒数第二个。
        {
            int start_node = req.route[request_choose_route][node];     //当前节点
            int end_node = req.route[request_choose_route][node + 1];   //下一个节点
            map_usage[start_node][end_node] += req.request_band_width;  //两个节点直接的流量加入到总图里
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
                if(map_usage[i][j] != 0)
                {
                    map_percentage[i][j] = 2;
                }
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
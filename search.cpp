#include "search.h"
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

extern int grid_topo_data[956][3];
extern int request_data[4001][500];
int map[500][500] = {0};

vector<request> request_vec[1000];

//你要完成的功能总入口
void search()
{
    make_map();

    for (int  i= 0; i < 500; ++i)
    {
        for (int j = 0; j < 500; ++j)
        {
            cout << map[i][j] << '\t';
        }
        cout << endl;
    }
}

void make_map()
{
    for (int data_num = 1; data_num < 956; ++data_num)
    {
        int row = grid_topo_data[data_num][0];
        int col = grid_topo_data[data_num][1];
        map[row][col] = grid_topo_data[data_num][2];
        map[col][row] = grid_topo_data[data_num][2];
    }
}

void make_request_vec()
{
//    int counter = 0;    //记录读取行
//    while (counter < 4001)
//    {
//        request_vec[10]
//        counter = counter + 4;
//    }
}
#include "search.h"
#include "lib_io.h"
#include "lib_time.h"
#include "cstdio"

int main(int argc, char *argv[])
{
    print_time("Begin");
	char *request[MAX_DATA_NUM];
    char *gridtopo[MAX_INFO_NUM];
	int request_line_num;
    int grid_topo_line_num;
    
    char *request_file = argv[1];

    request_line_num = read_file(request, MAX_DATA_NUM, request_file);

    printf("request file line num is :%d \n", request_line_num);
    if (request_line_num == 0)
    {
        printf("Please input valid request file.\n");
        return -1;
    }
	
    char *grid_topo_file = argv[2];

    grid_topo_line_num = read_file(gridtopo, MAX_INFO_NUM, grid_topo_file);

    printf("gridtopo file line num is :%d \n", grid_topo_line_num);
    if (grid_topo_line_num == 0)
    {
        printf("Please input valid gridtopo file.\n");
        return -1;
    }

    char *output_file = argv[3];

    search();

    release_buff(request, request_line_num);
	release_buff(gridtopo, grid_topo_line_num);

    print_time("End");

	return 0;
}


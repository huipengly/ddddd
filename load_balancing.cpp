#include "search.h"
#include "lib_time.h"
#include "cstdio"

char *output_file;

int main(int argc, char *argv[])
{
    print_time("Begin");

    output_file = argv[1];

    search();

    print_time("End");

	return 0;
}


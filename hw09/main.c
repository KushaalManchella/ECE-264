#include<stdio.h>
#include<stdlib.h>
#include"maze.h"

int main(int argc,char* argv[])
{
	char* basefile = argv[1]; 
	FILE* fp = fopen(basefile, "r");
	char* filename = "newsample.2.7x9";
	int num_row = 0;
	int num_col = 0;
	int row = 1;
	int col = 8;
	int location = 0;
	if(fp == NULL)
	{
		return EXIT_FAILURE;
	}

	
	

	find_maze_dimensions(fp, &num_row, &num_col);
	find_opening_location(fp);
	count_path_locations(fp);
	location = get_location_type(fp, row, col);
	represent_maze_in_one_line(filename ,fp);
    printf("=====\n");
	printf("row = %d\n", row);
	printf("column = %d\n", col);
	printf(" location = %d", location);



}

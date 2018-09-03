#include<stdio.h>
#include<stdlib.h>
#include 

int main(int argc, char* argv[]){

	Maze* maze = argv[1]; 
	FILE* fp = fopen(basefile, "r");
	char* filename = "newsample.2.7x9";
	int num_row = 0;
	int num_col = 0;
	int row = 0;
	int col = 0;
	if(fp == NULL)
	{
		return EXIT_FAILURE;
	}

	
	

	mallocmaze( num_rows, num_cols )
	free(maze);
	read_maze(fp);
	write_maze(filename, maze);




}

#include<stdio.h>
#include<stdlib.h>
#include"maze.h"



int main(int argc, char* argv[]){
	
	char* basefile = argv[1]; 
	FILE* fp = fopen(basefile, "r");
	char* filename = "newsample.2.7x9";
	int num_rows = 0;
	int num_cols = 0;
	if(fp == NULL)
	{
		return EXIT_FAILURE;
	}

	
	

	Maze* maze = malloc_maze( num_rows, num_cols );
	maze = read_maze(fp);
	write_maze(filename, maze);
	

	free_maze(maze);



}


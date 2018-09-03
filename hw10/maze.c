#include<stdio.h>
#include<stdlib.h>
#include"maze.h"

Maze* malloc_maze(int num_rows, int num_cols){

	Maze* maze = malloc(sizeof(*maze));

	maze -> num_cols = num_cols;
	maze -> num_rows = num_rows;

	maze -> cells = malloc(sizeof(*maze -> cells) * num_rows);




	if(maze -> cells == NULL)
	{
		free(maze -> cells);
		free(maze);
		return NULL;
	}

	for( int i =0; i < num_rows; i++)
	{
		
		maze -> cells[i] = malloc(sizeof(**maze -> cells) * num_cols);
	}

	return maze;

}

void free_maze(Maze* maze){
	

	for( int i = 0; i < maze -> num_rows; i++)
	{
		free(maze -> cells[i]);
	}

	free(maze -> cells);
	free(maze);	

}

void _find_maze_dimensions(FILE * fp, int * a_num_rows, int * a_num_cols) {

	fseek( fp, 0, SEEK_SET);   //setting pointer to start of file 
    *a_num_rows = *a_num_cols = 0;
	int temp = 0;
    int ch = 0;
 	while(ch != '\n')   //retreiving number of rows 
	{
		ch = fgetc(fp);
		(*a_num_rows)++;
	}
	*a_num_rows = *a_num_rows - 1;
    
	fseek(fp, 0, SEEK_END); // setting pointer to end of file
	int sz = ftell(fp);

	*a_num_cols = sz / *a_num_rows;

	temp = *a_num_cols;
	*a_num_cols = *a_num_rows;
	*a_num_rows = temp;
	
	


//	printf("a_num_cols = %d\n", *a_num_cols);		
//	printf("a_num_rows = %d\n", *a_num_rows);
}



Maze* read_maze(FILE* fp){

	fseek(fp, 0, SEEK_SET);

	int row_dim = 0;
	int col_dim = 0;
	char ch = 0;

	_find_maze_dimensions(fp, &row_dim, &col_dim);

	Maze* maze = malloc_maze(row_dim, col_dim);
	
	fseek(fp, 0, SEEK_SET);

	int rows = 0;
	int cols = 0;
	
	for(rows = 0; rows < maze -> num_rows; rows++)
	{
		for(cols = 0; cols<= maze -> num_cols; cols++)
		{
			ch = fgetc(fp);
			if(ch != '\n')
			{
				maze -> cells [rows][cols] = ch;
			}
		}
	}
	
	
	return maze;
	

}

bool write_maze(const char* filename, const Maze* maze){
	
	FILE* fc = fopen(filename, "w");
	char output = 0;

	if(fc == NULL)
	{
		return false;
	}

	for(int rows = 0; rows < maze -> num_rows; rows++)
	{
		for(int cols = 0; cols < maze -> num_cols; cols++)
		{
			output = maze -> cells[rows][cols];
			fputc(output, fc);
		}
		fputc('\n', fc);
	}

	fclose(fc);
	
	
	
	return true;
}

Maze* make_taller(const Maze* orig){
	
	Maze* tall_maze = malloc_maze((orig -> num_rows)*2 - 1, (orig -> num_cols));
	// First half 
	int cols = 0;
	int rows = 0;
	int max_rows = 0;
	int max_cols = 0;
	int rows_orig = 0;
	int cols_orig = 0;
	max_rows = orig -> num_rows;
	max_cols = orig -> num_cols;
	for(rows = 0; rows < max_rows; rows++)
	{
		for(cols =0 ; cols <= (max_cols) ; cols++)
		{
			tall_maze -> cells[rows][cols] = orig -> cells[rows][cols];
		}
	}
	

	printf("num_rows = %d", max_rows);
	printf("num_cols = %d", max_cols);
	rows_orig = max_rows - 1;;
	cols_orig = 0;

	while(rows_orig >= 0)
	{
		for(cols = 0; cols <= max_cols; cols++)
		{
			if( cols_orig >= max_cols || rows_orig >= max_rows)
			{
				break;
			}
			tall_maze -> cells[rows][cols] = orig -> cells[rows_orig][cols_orig];
			cols_orig += 1;
		}
	 rows = rows + 1;
	 rows_orig = rows_orig - 1;
	}
	
	
	return tall_maze;

	
}

Maze* make_wider(const Maze* orig){

	Maze* wide_maze = malloc_maze((orig -> num_rows), (orig -> num_cols)*2-1);

	int cols = 0;
	int rows = 0;
	
	for(rows = 0; rows < orig -> num_rows; rows++)
	{
		for(cols =0 ; cols <= orig -> num_cols; cols++)
		{
			wide_maze -> cells[rows][cols] = orig -> cells[rows][cols];
		}
	//	wide_maze -> cells[rows][cols+1] = '\n';
	}

	cols = orig -> num_cols;
	cols = cols - 1;

	for(rows = 0; rows < orig -> num_rows; rows++)
	{

		for(cols =0 ; cols < orig -> num_cols; cols++)
		{
			wide_maze -> cells[rows][cols] = orig -> cells[rows][cols];
	
		}
		wide_maze -> cells[rows][cols+1] = '\n';
	}

	return wide_maze;


}





	
















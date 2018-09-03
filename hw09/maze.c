#include <stdio.h>
#include <stdlib.h>
#include "maze.h"

void find_maze_dimensions(FILE * fp, int * a_num_rows, int * a_num_cols) {

	fseek( fp, 0, SEEK_SET);   //setting pointer to start of file 
    *a_num_rows = *a_num_cols = 0;
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
//	printf("a_num_cols = %d\n", *a_num_cols);		
//	printf("a_num_rows = %d\n", *a_num_rows);
}

int find_opening_location(FILE * fp) {
	
   fseek( fp, 0, SEEK_SET);
   int ch = 0;
   int opening_loc = 0;
   while(ch != PATH)     // finding opening location in first row 
   {
	   ch = fgetc(fp);
	   opening_loc++;
	   
	}
   opening_loc -= 1;
//   printf("opening location = %d\n", opening_loc);     
   return opening_loc;
}

int count_path_locations(FILE * fp) {
	fseek( fp, 0, SEEK_SET);
	int ch = 0;
	int num_locations = 0;
	while(!feof(fp))    // Calculating number of paths 
	{
		ch = fgetc(fp);
		if( ch == PATH)
		{
			num_locations++;
		}
	}
//	printf("num locations = %d\n", num_locations);	 
	return num_locations;
}

char get_location_type(FILE * fp, int row, int col) {
	fseek( fp, 0, SEEK_SET);
	int ch = 0;
	int location = 0;
	int path_loc = 0;
	int col_count = 0;
	int row_count = 0;
	while(!feof(fp))    // while loop to find WALL or PATH at each location 
	{	
		ch = fgetc(fp);
		if(ch != '\n')
		{
			location = ch;
			col_count++;
			if((row_count) == row && (col_count-1) == col)
			{
				
				break;
			}

		}
		else 
		{
			col_count = 0;
			row_count++;
			if((row_count-1) == row && (col_count) == col)
			{		
				break;
			}

		}
	
	}
	
	if( row == 0 && col == 0)  // EXCEPTION case 
	{
		location = fgetc(fp);
	}

	if(location == 88)
	{
		path_loc = WALL;
	}
	else
	{
		path_loc = PATH;
	}
	
	return path_loc;
}
 
int represent_maze_in_one_line(char * filename, FILE * fp) {
	
	FILE *fc = fopen(filename, "w");
	fseek(fp, 0, SEEK_SET);
	int ch = 0;
	int k = 0; // counter for while loop 

	if(fc == NULL)
	{
		return MAZE_WRITE_FAILURE;
	}
	
	while(!feof(fp))
	{	
		ch = fgetc(fp);
		
		if(ch != '\n' && ch!= EOF)
		{
			fputc(ch, fc);
			k++;
		}
//		printf("k is %d\n", k);		 
	}
	fclose(fc);


    return k;
}

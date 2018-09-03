#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include "maze.h"



static bool is_path(Maze *maze, int row, int col)
{
   if ((row >= 0) && (row < maze->n_row)) {
      if ((col >= 0) && (col < maze->n_col)) {
         return maze->maze_array[row][col] == PATH;
      }
   }
   return false;
}

Maze* malloc_maze(int n_row, int n_col){

	Maze* maze = malloc(sizeof(*maze));

	maze -> n_col = n_col;
	maze -> n_row = n_row;

	if(maze == NULL)
	{
		free(maze);
		return NULL;
	}


	maze -> maze_array = malloc(sizeof(maze -> maze_array) * n_row);




	if(maze -> maze_array  == NULL)
	{
		free(maze -> maze_array);
		free(maze);
		return NULL;
	}

	for( int i =0; i < n_row; i++)
	{
		
		maze -> maze_array[i] = malloc(sizeof(maze -> maze_array[i]) * n_col);

		if(maze -> maze_array[i] == NULL)
		{
			while(i > 0)
			{
				free(maze -> maze_array[i]);
				i--;
			}
		
			free(maze -> maze_array);
			free(maze);
			return NULL;
		}
	
	}


	return maze;

}


void free_maze(Maze* maze){
	

	for( int i = 0; i < maze -> n_row; i++)
	{
		free(maze -> maze_array[i]);
	}

	free(maze -> maze_array);
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
	
	for(rows = 0; rows < maze -> n_row; rows++)
	{
		for(cols = 0; cols<= maze -> n_col; cols++)
		{
			ch = fgetc(fp);
			if(ch != '\n')
			{
				maze -> maze_array [rows][cols] = ch;
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

	for(int rows = 0; rows < maze -> n_row; rows++)
	{
		for(int cols = 0; cols < maze -> n_col; cols++)
		{
			output = maze -> maze_array[rows][cols];
			fputc(output, fc);
		}
		fputc('\n', fc);
	}

	fclose(fc);
		
	return true;
}


/* given a maze, current row (curr),                                     */
/* current column (curc), destination row (drow), destination col (dcol) */
/* current distance from source, determine the where to explore from the */
/* current location                                                      */
/* a recursive function: from the current location, try 'N', 'S', 'E',   */
/* 'W' locations one at a time if the attempt is successful, write the   */
/* direction in the file                                                 */




static int _pathfinder_helper(Maze *maze, int curr, int curc, int endr, int endc,
                            int count, FILE *dfptr)
{
   // you may uncomment this and use the output here to trace the function
   // with sample5.pdf
   // printf("(%d, %d), %d\n", curr, curc, count);
   maze->maze_array[curr][curc] = VISITED;
   if ((curr == endr) && (curc == endc)) { // reach the destination 
      int i;
      for (i = 0; i < count; i++) { // create enough space in file
         fputc(VISITED, dfptr);
      }
      return count;
   }

   int found;
   if (is_path(maze, curr-1, curc)) {
      found = _pathfinder_helper(maze, curr-1, curc, endr, endc, count+1, dfptr);
      if (found != -1) {
         fseek(dfptr, -1, SEEK_CUR); // go back one position
         fputc('N', dfptr);
         fseek(dfptr, -1, SEEK_CUR); // go back one position
         return found;
      }
   }
   if (is_path(maze, curr+1, curc)) {
      found = _pathfinder_helper(maze, curr+1, curc, endr, endc, count+1, dfptr);
      if (found != -1) {
         fseek(dfptr, -1, SEEK_CUR); // go back one position
         fputc('S', dfptr);
         fseek(dfptr, -1, SEEK_CUR); // go back one position
         return found;
      }
   }
   if (is_path(maze, curr, curc+1)) {
      found = _pathfinder_helper(maze, curr, curc+1, endr, endc, count+1, dfptr);
      if (found != -1) {
         fseek(dfptr, -1, SEEK_CUR); // go back one position
         fputc('E', dfptr);
         fseek(dfptr, -1, SEEK_CUR); // go back one position
         return found;
      }
   }
   if (is_path(maze, curr, curc-1)) {
      found = _pathfinder_helper(maze, curr, curc-1, endr, endc, count+1, dfptr);
      if (found != -1) {
         fseek(dfptr, -1, SEEK_CUR); // go back one position
         fputc('W', dfptr);
         fseek(dfptr, -1, SEEK_CUR); // go back one position
         return found;
      }
   }
   return -1;
}

/* this is a function implemented by the instructor to illustrate           */
/* how to use a recursive function to go from the left-most top entrance to */
/* the right-most bottom exit of a maze.  The function will print the       */
/* directions taken to reach the bottom exit, without visiting a location   */
/* twice.  Note that the recursion may visit a location a few times         */
/* Given three filenames, first one is a given maze, the second one is to   */
/* be written with the directions, the third is the explored maze           */
/* If the maze file does not exist, the function immediately return -1 and  */
/* do nothing else                                                          */
/* the directions are in the form of a series of characters                 */
/* 'N', 'S', 'E', 'W', without spacing (and without the quotes).            */
/* There should be just a single line, without a terminating newline        */
/* character. In other words, to the vi editor, it is an incomplete file    */
/* you are to assume that you start from the top-most, left-most entry      */
/* of the maze.  Therefore, the first direction is always 'S'               */
/* similarly, the last direction is always 'S'                              */
/* the returned value should be the number of steps taken to reach          */
/* the right-most bottom exit.  It is typically not the shortest distance   */
/* Note that the maze can be generated by amaze, or some combinations of    */
/* the maze expansion functions that you have written in PE08               */
/* you may assume that the maze file, if it exists, is in the correct format*/

int find_path_from_top_entrance_to_bottom_exit(char *maze_file, char *directions_file, char *visited_file)
{
   FILE *mfptr = fopen(maze_file, "r");
   if (mfptr == NULL) {
      return -1;
   }
   
   /* read the maze from mfptr */

   Maze *maze = read_maze(mfptr);
   fclose(mfptr);
   if (maze == NULL) {
      return -1;
   }
   
   /* find the starting location, the top-most, left-most opening */
   int startr, startc;
   startr = 0;
   for (startc = 0; startc < maze->n_col; startc++) {
      if (maze->maze_array[startr][startc] == PATH) {
         break;
      }
   }

   /* find the ending location, the bottom-most, right most opening */
   int endr, endc;
   endr = maze->n_row-1;
   for (endc = maze->n_col-1; endc >= 0; endc--) {
      if (maze->maze_array[endr][endc] == PATH) {
         break;
      }
   } 

   // no starting location, deallocate and return 
   if (startc == maze->n_col) {
      free_maze(maze);
      return -1;
   }
   // no ending location, deallocate and return 
   if (endc == -1) {
      free_maze(maze);
      return -1;
   }

   FILE *dfptr = fopen(directions_file, "w");
   if (dfptr == NULL) {
      free_maze(maze);
      return -1;
   }
   int steps = _pathfinder_helper(maze, startr, startc, endr, endc, 0, dfptr);
   write_maze(visited_file, maze);
   fclose(dfptr);
   free_maze(maze);
   return steps;
}

int _not_wall(Maze *maze, Maze *copy, int row, int col)
{
	if(maze -> maze_array[row][col] != WALL || copy -> maze_array[row][col] != WALL)
	{
		return 0;
	}
	return 1;
}

int _pathfinder(Maze* maze, Maze* copy, int i, int j, int row, int col, int final, int dist)
{
	int count = 0;
	if( i == row && j == col)
	{
		if(dist < final)
		{
			final = dist;
		}
		return count;
	}
	copy -> maze_array[i][j] = PATH;
	if(is_path(maze, i+1, j) && _not_wall(maze, copy, i+1, j))
	{
		count +=1;
		_pathfinder(maze, copy, i+1 ,j , row, col, final, dist + 1);
		
	}
	if(is_path(maze, i, j+1) && _not_wall(maze, copy, i, j+1))
	{	
		count +=1;
		_pathfinder(maze, copy, i ,j+1 , row, col, final, dist + 1);
	}
	if(is_path(maze, i-1, j) && _not_wall(maze, copy, i-1, j))
	{
		count +=1;
		_pathfinder(maze, copy, i ,j-1 , row, col, final, dist + 1);
	}
	if(is_path(maze, i, j-1) && _not_wall(maze, copy, i, j-1))
	{
		count +=1;
		_pathfinder(maze, copy, i ,j-1 , row, col, final, dist + 1);
	}
	return count;
}

int dfs_shortest_path_directions(char *maze_file, char *directions_file,
                        Coord source, Coord destination)
{
	int steps = 0;
	FILE *mfptr = fopen(maze_file, "r");
   if (mfptr == NULL) {
      return -1;
   }
   
   /* read the maze from mfptr */

   Maze *maze = read_maze(mfptr);
   Maze *copy = malloc_maze(maze -> n_row, maze -> n_col);

   fclose(mfptr);
   if (maze == NULL) {
      return -1;
   }
   
   /* find the starting location, the top-most, left-most opening */
   int startr, startc;
   startr = 0;
   for (startc = 0; startc < maze->n_col; startc++) {
      if (maze->maze_array[startr][startc] == PATH) {
         break;
      }
   }

   /* find the ending location, the bottom-most, right most opening */
   int endr, endc;
   endr = maze->n_row-1;
   for (endc = maze->n_col-1; endc >= 0; endc--) {
      if (maze->maze_array[endr][endc] == PATH) {
         break;
      }
   } 

   // no starting location, deallocate and return 
   if (startc == maze->n_col) {
      free_maze(maze);
      return -1;
   }
   // no ending location, deallocate and return 
   if (endc == -1) {
      free_maze(maze);
      return -1;
   }

   FILE *dfptr = fopen(directions_file, "w");
   if (dfptr == NULL) {
      free_maze(maze);
      return -1;
   }
   steps = _pathfinder(maze, copy, startr, startc, endr, endc, 0, 0);
   fclose(dfptr);
   free_maze(copy);
   return steps;

	
   return -1;
}

int simulate_movement(char *maze_file, char *directions_file, char *visited_file,
                      Coord source, Coord destination)
{
	FILE *Fc = fopen(maze_file,"r");
	FILE *Fp = fopen(directions_file,"r");
	char ch = 0;
	int count = 0;
	int row = source.row;
	int col = source.col;

	Maze* directions =read_maze(Fc);
	
	while(!feof(Fp))
	{
		ch = fgetc(Fp);

		if( ch == 'N')
		{
			row = row - 1;
			directions -> maze_array[row][col] = VISITED;
		}
		else if( ch == 'W')
		{	
			 col = col - 1;
			directions -> maze_array[row][col] = VISITED;

		}
		else if( ch == 'E')
		{
			col = col + 1;
			directions -> maze_array[row][col] = VISITED;

		}
		else if( ch == 'S')
		{
			row = row + 1;	
			directions -> maze_array[row][col] = VISITED;
		}

		count += 1; 

	}
	
	write_maze(visited_file, directions);
	fclose(Fp);
	fclose(Fc);

   return count;
}


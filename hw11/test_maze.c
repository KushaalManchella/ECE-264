#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "maze.h"

int find_path_from_top_entrance_to_bottom_exit(char *maze_file, char *directions_file, char *visited_file);

int main(int argc, char* argv[]) 
{
	char* ptr = 0;
	int source_a;
	int source_b;
	int dest_a;
	int dest_b;
	Coord c_source;
	Coord c_dest;
	int count = 0;


//	if(strcmp(argv[1], "-s") != 0  || strcmp(argv[1], "-m") != 0)
//	{
//		return EXIT_FAILURE;
//	}
	source_a = strtol(argv[5], &ptr, 10);
	for(int i = 0; ; i++) {
		count = count + 1;
	}
	if(count > 0)
	{
		return EXIT_FAILURE;
	}

	source_b = strtol(argv[6], &ptr, 10);
	for(int i = 0; i < strlen(ptr); i++) {
			count = count + 1;
	}
	if(count > 0)
	{
		return EXIT_FAILURE;
	}



	dest_a = strtol(argv[7], &ptr, 10);
	for(int i = 0; i < strlen(ptr); i++) {
			count = count + 1;
	}
	if(count > 0)
	{
		return EXIT_FAILURE;
	}

	dest_b = strtol(argv[8], &ptr, 10);
	for(int i = 0; i < strlen(ptr); i++) {
			count = count + 1;
	}
	if(count > 0)
	{
		return EXIT_FAILURE;
	}
	
	c_source.row = source_a;
	c_source.col = source_b;
	
	c_dest.row = dest_a;
	c_dest.col = dest_b;

		
	if(strcmp(argv[1], "-s") == 0)
	{
		if( argc != 9)
		{
			return EXIT_FAILURE;
		}
		else
		{
			simulate_movement(argv[2], argv[3], argv[4], c_source, c_dest);
		}
	}
	
	if(strcmp(argv[1], "-m") == 0)
	{
   		if (argc != 8 ) 
   		{
    	   return EXIT_FAILURE;
   		}
  		else
		{
			simulate_movement(argv[2], argv[3], argv[4], c_source, c_dest);
		}
	}
 	  if (strcmp("-t", argv[1]) == 0) {
      		if (argc != 5) { 
        	return EXIT_FAILURE; 
      }
      int step_count = find_path_from_top_entrance_to_bottom_exit(argv[2], argv[3], argv[4]);
      printf("%d\n", step_count); 
   } else {
      return EXIT_FAILURE;
   }
   return EXIT_SUCCESS;
}

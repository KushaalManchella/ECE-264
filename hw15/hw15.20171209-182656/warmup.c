#include<stdio.h>
#include<string.h>
#include<stdlib.h>


typedef struct _Point{
		int x;
		int y;
	} Point;



char* read_file(const char* path,char** error ){
	FILE* fp = fopen(path, "r");
	if (fp == NULL)
	{
		printf("%s\n", *error);
		return NULL;
	}

	fseek(fp, 0, SEEK_END);
	int num = ftell(fp); // number of members
	fseek(fp, 0, SEEK_SET);
	
	char* output  = malloc(sizeof(*output)*num+1);
	output[num] = '\0';

	fread(output, sizeof(char), num, fp);
	fclose(fp);

	return output;
}

void write_file(const char* path, const char* contents, char** error){
	FILE* fp = fopen(path,"w");

	if(fp == NULL)
	{
		printf("%s\n", *error);
		return;
	}

	int size = strlen(contents);
	fwrite(contents, sizeof(char), size, fp);
	fclose(fp);

}

void write_point(char* path, Point coord, char** error){
	FILE* fp = fopen(path, "w");
	
	if (fp == NULL)
	{
		printf("%s\n", *error);
		return ;
	}


	fseek(fp, 0, SEEK_SET);
	
	fwrite(&coord, sizeof(Point), 1, fp);
	fclose(fp);

}

Point read_point(const char* path, char** error){
	Point A = {.x = 0, .y = 0}; 

	FILE* fp = fopen(path, "r");

	if (fp == NULL)
	{
		printf("%s\n", *error);
	}


	fseek(fp, 0, SEEK_SET);

	fread(&A ,sizeof(Point), 1, fp);
	fclose(fp);

	return A;

}


int main(int argc, char* argv[]){
		
	
	char* error = "You have an error";
	char* input = "test3.txt";
	char* output_file = "test1.txt";
	char* output_point = "test2.txt";

	
	char* res = read_file(input, &error);
	write_file(output_file, res , &error);

	Point coord = {.x = 6, .y = 7};
	
	write_point(output_point ,coord , &error);  // not sure if this works 
	Point output_coord = read_point(output_point , &error);

	printf("output_coord.x = %d, output_coord.y = %d\n", output_coord.x, output_coord.y);
	return 0;	
}






	




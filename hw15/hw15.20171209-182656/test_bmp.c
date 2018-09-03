#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"bmp.h"

int main(int argc, char* argv[]){
	char* error = "You have an error, reconsider your life\n";

	FILE* fp = fopen("6x6_24bit.bmp", "r");
	FILE* fc = fopen("copy.bmp","w");
	FILE *fd = fopen("crop.bmp","w");


	BMPImage* image = read_bmp(fp ,&error);
	if(image == NULL){

		printf("could not read file\n");
		return false; // failure
	}

	
	bool yes = write_bmp(fc, image, &error);
	if(!yes)
	{
		printf("could not write file\n");
		return false; // failure 
	}


	printf("BMP files were successfully read, written on and cropped\n");
	

	free_bmp(image);
	fclose(fp);
	fclose(fc);
	fclose(fd);



	return EXIT_FAILURE;

}

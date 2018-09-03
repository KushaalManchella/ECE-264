#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"bmp.h"

int main(int argc, char* argv[]){
	char* error = NULL; 

	FILE* fp = fopen("6x6_24bit.bmp", "r");
	FILE* fc = fopen("copy.bmp","w");
	FILE *fd = fopen("crop.bmp","w");


	BMPImage* img = read_bmp(fp ,&error);
	if(img == NULL)
	{

		printf("%s\n", error);
		free(error);
		free_bmp(img);
		fclose(fp);
		fclose(fc);
		fclose(fd);
		return EXIT_FAILURE; // failure
	}


// printf("image -> header.size  %d\n", image -> header.size);

bool yes = write_bmp(fc, img, &error);
	if(!yes)
	{
		printf("%s\n", error);
		free(error);
		free_bmp(img);
		fclose(fp);
		fclose(fc);
		fclose(fd);
		return EXIT_FAILURE; // failure 
	}

/*	yes = crop_bmp( img, 4, 1, 1, 1, &error);
	if(!yes)
	{
		printf("%s\n", error);
		free(error);
		free_bmp(img);
		fclose(fp);
		fclose(fc);
		fclose(fd);
		return EXIT_FAILURE; // failure 
	}
*/


	printf("BMP files were successfully read, written on and cropped\n");
	

	free_bmp(img);
	fclose(fp);
	fclose(fc);
	fclose(fd);



	return EXIT_SUCCESS;

}

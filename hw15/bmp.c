#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"bmp.h"


BMPImage* read_bmp(FILE* fp, char** error){

	BMPImage* image = malloc(sizeof(BMPImage));


	if(image == NULL)
	{
		char* error_mes = "Malloc failed";
		*error = malloc((strlen(error_mes) +1) * sizeof(**error));
		strcpy(*error, error_mes);
		free(image -> data);
		free(image);
		return NULL;
	}	

// reading header 
	
	fseek(fp, 0, SEEK_SET);
	int count = fread(&(image->header), sizeof(BMPHeader), 1, fp);

// checking for errors in fread for header 
	if(count != 1){
		char* error_mes = "BMP header is invalid";
		*error = malloc((strlen(error_mes)+1) * sizeof(**error));
		strcpy(*error, error_mes);
		free(image);
		return NULL;
	 }

	image -> data = malloc(sizeof(char) * (image -> header.size - BMP_HEADER_SIZE));
	if(image -> data == NULL)
	{
		char* error_mes = "malloc error";
		*error = malloc((strlen(error_mes)+1) * sizeof(**error));
		strcpy(*error, error_mes);
		free(image -> data);
		free(image);
		return NULL; // failure

	}

	fseek(fp, BMP_HEADER_SIZE, SEEK_SET);
	count = fread(image->data, sizeof(char), (image->header.size - BMP_HEADER_SIZE), fp);

// checking for errors in fread for image data 

	if(count != image -> header.size - BMP_HEADER_SIZE){
		char* error_mes = "unable to read file";
		*error = malloc((strlen(error_mes)+1) * sizeof(**error));
		strcpy(*error, error_mes);
		free(image -> data);
		free(image);
		return NULL; // failure
	 }

	bool yes = check_bmp_header(&(image->header), fp);
	if(!yes)
	{
		char* error_mes = "invalid bmp header";
		*error = malloc((strlen(error_mes)+1) * sizeof(**error));
		strcpy(*error, error_mes);
		free(image -> data);
		free(image);
		return NULL;
	}


	return image;
}


bool check_bmp_header(BMPHeader* bmp_hdr, FILE* fp){
	// magic number test
	if( bmp_hdr -> type != 0x4d42){
		return false;
	}
	if( bmp_hdr -> offset != BMP_HEADER_SIZE){
		return false;
	}
	if( bmp_hdr -> dib_header_size != DIB_HEADER_SIZE){
		return false;
	}
	if( bmp_hdr -> num_planes != 1){
		return false;
	}
	if( bmp_hdr -> compression != 0){
		return false;
	}
	if(( bmp_hdr -> num_colors != 0) ||( bmp_hdr -> important_colors != 0)){
		return false;
	}
	if( bmp_hdr -> bits_per_pixel != 24){
		return false;
	}
	if( bmp_hdr -> size != ftell(fp)){
		return false;
	}
	int num = (bmp_hdr -> width_px * 3) % 4;
	int row_pad= 4 - num;
	row_pad %= 4;

	int total_pad = row_pad * bmp_hdr -> height_px;

	if(bmp_hdr -> image_size_bytes != (bmp_hdr -> width_px * bmp_hdr -> height_px * 3) + total_pad)
	{
		return false;
	}

	return true;

}

bool write_bmp(FILE* fp, BMPImage *image, char** error)
{
	int count = fwrite(&(image->header), sizeof(BMPHeader), 1, fp);

	if(count != 1)
	{
		char* error_mes = "unable to write to file";
		*error = malloc((strlen(error_mes)+1) * sizeof(**error));
		strcpy(*error, error_mes)	;	
		return false; // failure
	 }

	count = fwrite(image -> data, sizeof(char), (image -> header.size - BMP_HEADER_SIZE), fp);
	if(count != image -> header.size - BMP_HEADER_SIZE)
	{	
		char* error_mes = "unable to write to file";
		*error = malloc((strlen(error_mes)+1) * sizeof(**error));
		strcpy(*error, error_mes);
		return false; // failure
	 }

	return true;
}


void free_bmp(BMPImage *image){
	free(image -> data);
	free(image);
}

/*
BMPImage* crop_bmp(BMPImage* image, int x, int y, int w, int h, char** error){

	int pad = 0;
	int row_pad = 0;
	int total_pad = 0;

	BMPImage* image_copy = malloc(sizeof(image));
	if(image_copy == NULL)
	{
		char* error_mes = "Malloc failed";
		*error = malloc((strlen(error_mes)+1)*sizeof(**error));
		strcpy(*error, error_mes);
		return image;
	}

	image_copy -> header = image -> header;


	// account or padding 
	
	pad = (w * 3) % 4;
	row_pad = 4 - pad;
	row_pad = row_pad % 4;
	total_pad = row_pad * h;

	image_copy -> header.image_size_bytes = total_pad + (w * 3 * h);
	image_copy -> header.size = (image_copy -> header.image_size_bytes) + BMP_HEADER_SIZE;
	image_copy -> header.width_px = w;
	image_copy -> header.height_px = h;

	image_copy = malloc(sizeof(char) * (image_copy -> header.image_size_bytes));
	if(image_copy -> data == NULL)
	{
		char* error_mes = "Malloc Failure";
		*error = malloc((strlen(error_mes)+1) * sizeof(**error));
		strcpy(*error, error_mes);
		return image_copy;
	}

	return image_copy;

}
*/
	



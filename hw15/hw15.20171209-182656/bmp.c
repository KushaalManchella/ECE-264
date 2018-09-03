#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"bmp.h"


BMPImage* read_bmp(FILE* fp, char** error){

	BMPImage* image = malloc(sizeof(BMPImage));



	if(image == NULL)
	{
		*error = "Failed to allocate memory";
		return NULL;
	}


// reading header 
	
	size_t count = fread(&(image->header), sizeof(BMPHeader), 1, fp);

	check_bmp_header(&(image->header), fp);

// checking for errors in fread for header 
	if(count != 1){
		const char* temp_error = "unable to read file";
		char* error_mes = malloc(sizeof(*error_mes)*(strlen(temp_error) + 1));
	   	strcpy(error_mes, temp_error);
		*error = error_mes;
		free(image);
		return false; // failure
	 }

	image -> data = malloc(sizeof(char) * (image -> header.size - BMP_HEADER_SIZE));
	if(image -> data == NULL)
	{
		*error = "Failed to allocate memory to picture -> data";
	}

	fseek(fp, BMP_HEADER_SIZE, SEEK_SET);
	count = fread(image->data, sizeof(char), (image->header.size - BMP_HEADER_SIZE), fp);

// checking for errors in fread for image data 

	if(count != image -> header.size - BMP_HEADER_SIZE){
		const char* temp_error = "unable to read file";
		char* error_mes = malloc(sizeof(*error_mes)*(strlen(temp_error) + 1));
	   	strcpy(error_mes, temp_error);
		*error = error_mes;
		free(image -> data);
		free(image);
		return false; // failure
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
	if( bmp_hdr -> dib_header_size != 40){
		return false;
	}
	if( bmp_hdr -> num_planes != 1){
		return false;
	}
	if( bmp_hdr -> compression != 0){
		return false;
	}
	if( bmp_hdr -> num_colors != 0 || bmp_hdr -> important_colors != 0){
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

	if(bmp_hdr -> image_size_bytes != (bmp_hdr -> width_px * bmp_hdr -> height_px * 3) * total_pad){
		return false;
	}

	return true;

}

bool write_bmp(FILE* fp, BMPImage *image, char** error){
	size_t count = fwrite(&(image->header), sizeof(BMPHeader), 1, fp);

	if(count != 1){
		const char* temp_error = "unable to write to file";
		char* error_mes = malloc(sizeof(*error_mes)*(strlen(temp_error) + 1));
	   	strcpy(error_mes, temp_error);
		*error = error_mes;
		return false; // failure
	 }

	count = fwrite(image -> data, sizeof(char), (image -> header.size - BMP_HEADER_SIZE), fp);
	if(count != image -> header.size - BMP_HEADER_SIZE)
	{	
		const char* temp_error = "unable to write to file";
		char* error_mes = malloc(sizeof(*error_mes)*(strlen(temp_error) + 1));
	   	strcpy(error_mes, temp_error);
		*error = error_mes;
		return false; // failure
	 }

	return true;
}


void free_bmp(BMPImage *image){
	free(image -> data);
	free(image);
}






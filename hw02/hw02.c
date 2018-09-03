#include<stdio.h>
#include "hw02.h"

void print_integer(int n,int radix, char* prefix){
	char convert = '0'; 	// adds decimal value 48 to n to obtain the intended character from ASCII chart
	unsigned int val = n; 	// value of n used in calculation ( value which is displayed in base radix with a prefix )

	if( n < 0){
		val *= -1;	 // accounting for a negative n 
		fputc('-',stdout); // printing a negative sign 
	}

	for(int idx_in_s = 0; prefix[idx_in_s] != '\0'; idx_in_s++){
		fputc(prefix[idx_in_s], stdout); 
	}

	int remainder = val % radix; 	// calculating remainder 

	remainder >= 10 ? convert = 'W' : convert ;

	if(val / radix > 0)	{
		print_integer(val / radix, radix, "");	 // use of recursion to update remainder 
	}

	fputc(remainder+convert, stdout);

}

		







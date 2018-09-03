#include <stdio.h>
#include <stdlib.h>
#include "hw02.h"
#include "limits.h"


int main(int argc, char* argv[])
{
	print_integer(7658336,10, "");
	fputc(10,stdout);

   	print_integer(51,2,"A");
	fputc(10,stdout);

	print_integer(151269,4,"D");
	fputc(10,stdout);

	print_integer(-2958,5,"G");
	fputc(10,stdout);

	print_integer(2958,5,"G");
	fputc(10,stdout);

	print_integer(63834,9,"B");
	fputc(10,stdout);

	print_integer(8822,10,"C");
	fputc(10,stdout);

	print_integer(75677351,11,"U");
	fputc(10,stdout);

	print_integer(-3952,13,"X");
	fputc(10,stdout);

	print_integer(3952,13,"X");
	fputc(10,stdout);

	print_integer(925572,15,"F");
	fputc(10,stdout);

	print_integer(1111,22,"Z");
	fputc(10,stdout);

	print_integer(28111997,30,"H");
	fputc(10,stdout);
 
    print_integer(29573,36,"Y");
	fputc(10,stdout);

	print_integer(0, 35 ,"Y");
	fputc(10,stdout);

	print_integer(INT_MIN + 1, 10, ""); // test case 
    fputc(10, stdout);	
    
	return EXIT_SUCCESS;
}


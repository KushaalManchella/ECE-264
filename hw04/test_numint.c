#include <stdio.h>
#include <stdlib.h>
#include "aux.h"
#include "string.h"
// do not change this part, if you do, your code may not compile
//
/* test for structure defined by student */
#ifndef NTEST_STRUCT 
#include "numint.h"
#else
#include "numint_key.h"
#endif /* NTEST_STRUCT */
//
// do not change above this line, if you do, your code may not compile

      
int main(int argc, char * * argv)
{   
	double integral = 0.0;
    Integrand intg_arg = { .lower_limit = 0, .upper_limit = 0, .n_intervals = 0, .func_to_be_integrated = unknown_function_1 };
   

    if(argc != 5){ // testing to see if there are exactly 5 arguments 
		return EXIT_FAILURE;
	}

	// converting arguments to correct data types 
 	intg_arg.lower_limit = atof(argv[2]);
   	intg_arg.upper_limit = atof(argv[3]);
	intg_arg.n_intervals = atoi(argv[4]);
	
	if(intg_arg.n_intervals < 1){ // ensuring that intervals remain greater than or equal to 1 
		intg_arg.n_intervals = 1;
	}
	// method for selecting which function to use 
	if(strcmp(argv[1],"1") == 0){
		intg_arg.func_to_be_integrated = unknown_function_1;
	}
	else if(strcmp(argv[1],"2") == 0){
		intg_arg.func_to_be_integrated = unknown_function_2;
	}
	else if(strcmp(argv[1],"3") == 0){
		intg_arg.func_to_be_integrated = unknown_function_3;
	}
	else{
		return EXIT_FAILURE;
	}

   integral = simpson_numerical_integration(intg_arg);

   printf("%.10e\n", integral);
   return EXIT_SUCCESS;
}

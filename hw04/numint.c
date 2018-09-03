//do not change this part, if you do, your code may not compile
//
/* test for structure defined by student */
#include <stdio.h>
#ifndef NTEST_STRUCT 
#include "numint.h"
#else 
#include "numint_key.h"
#endif /* NTEST_STRUCT */
//
// do not change above this line, if you do, your code may not compile
// This is the only file you have to include 
double simpson_numerical_integration(Integrand intg_arg){		   
   double integral = 0.0;
   double interval = 0.0;
   double integral_sum = 0.0;
   int count = 0; // counter used for for loop that gets summation
   double lower_limit = intg_arg.lower_limit;
   double upper_limit = intg_arg.upper_limit;

   interval = (upper_limit -lower_limit)/intg_arg.n_intervals; // calculating interval

   for(count = 0; count < intg_arg.n_intervals; count ++){
		lower_limit = intg_arg.lower_limit + interval*(count);
		upper_limit = intg_arg.lower_limit + interval*(count + 1);
		integral_sum = ((interval)/6) *(intg_arg.func_to_be_integrated(lower_limit) + 4 * intg_arg.func_to_be_integrated((lower_limit + upper_limit)/2) + intg_arg.func_to_be_integrated(upper_limit));
		integral += integral_sum;}
   
   return integral;}
                       	       			            		 		 		 		 		 					   

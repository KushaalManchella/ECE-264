#include <math.h>
#include "fourier.h"
#define M_PI 3.141592653589793115997963468544185161590576171875L
#include <stdio.h>

double simpson_numerical_integration(Integrand intg_arg) {
   double integral = 0.0;
   double integral_sum = 0.0;
   double interval = 0.0;
   int count = 0; // counter used for for loop that gets summation
   double lower_limit = intg_arg.lower_limit;
   double upper_limit = intg_arg.upper_limit;

   interval = (upper_limit -lower_limit)/intg_arg.n_intervals; // calculating interval

   while(count < intg_arg.n_intervals)   // summation to calculate simpson's integration method 
   {
   		lower_limit = intg_arg.lower_limit + interval*(count);
		upper_limit = intg_arg.lower_limit + interval*(count + 1);
		integral_sum = ((interval)/6) *(intg_arg.func_to_be_integrated(lower_limit) + 4 * intg_arg.func_to_be_integrated((lower_limit + upper_limit)/2) + intg_arg.func_to_be_integrated(upper_limit));
		integral += integral_sum;

		count += 1;
	}
   
   return integral;
}

double simpson_numerical_integration_for_fourier(Integrand intg_arg, int n, 
                                                 double (*cos_sin)(double)) {
   double integral = 0.0;
   double integral_sum = 0.0;
   double interval = 0.0;
   double L = (intg_arg.upper_limit - intg_arg.lower_limit)/2;
   int count = 0;
   double lower_limit = intg_arg.lower_limit;
   double upper_limit = intg_arg.upper_limit;
   double f_lower_lim;
   double f_upper_lim;
   double f_mid_point;

   interval = (upper_limit - lower_limit)/ intg_arg.n_intervals; 

   while(count < intg_arg.n_intervals ) // summation to calculate simpson's integration method for fourier
   {
   		lower_limit = intg_arg.lower_limit + interval*(count);
		upper_limit = intg_arg.lower_limit + interval*(count + 1);
		f_lower_lim = intg_arg.func_to_be_integrated(lower_limit) * cos_sin((n*M_PI* (lower_limit))/L);
		f_upper_lim = intg_arg.func_to_be_integrated(upper_limit) * cos_sin((n*M_PI* (upper_limit))/L);
		f_mid_point = intg_arg.func_to_be_integrated((upper_limit + lower_limit)/2) * cos_sin((n*M_PI* ((lower_limit + upper_limit)/2))/L);
		integral_sum = ((interval)/6) *(f_lower_lim + 4 * f_mid_point + f_upper_lim);
		
 		integral += integral_sum;
		count += 1;
	}
  
   return integral;
}

void fourier_coefficients(Fourier fourier_arg) {
   double L = (fourier_arg.intg.upper_limit - fourier_arg.intg.lower_limit)/2;
   for (int i = 0; i < fourier_arg.n_terms; i++) {
      fourier_arg.a_i[i] = 0.0;
      fourier_arg.b_i[i] = 0.0;
   }

   fourier_arg.a_i[0] = (1/L) * simpson_numerical_integration(fourier_arg.intg);
  
 

    
	for(int i = 1; i < fourier_arg.n_terms; i++)
   {
   		fourier_arg.a_i[i] = (1/L) * simpson_numerical_integration_for_fourier(fourier_arg.intg, i, cos);
		fourier_arg.b_i[i] = (1/L) * simpson_numerical_integration_for_fourier(fourier_arg.intg, i, sin);
	}



	return;
}

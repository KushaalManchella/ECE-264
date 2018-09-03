#include<stdio.h>
#include<stdlib.h>
#include<stdarg.h>
#include "mintf.h"
#include<limits.h>


void mintf(const char* format, ...)
{
	
	va_list more_args;
	va_start(more_args, format);

	int i = 0;	
	int j = 0;
	char* character_array;
    int true_val = 0;
	while(format[i] != '\0')
	{
		if(format[i] != '%')
		{
			fputc(format[i], stdout);
		}
		else if(format[i] == '%')
		{
				if(format[i+1] == 'd')
				{	
			//		if( va_arg(more_args, int) > INT_MIN && va_arg(more_args, int) < INT_MAX)
			//		{
						print_integer(va_arg(more_args, int) , 10, "");
						i++;
			//		}
				}
				else if(format[i+1] == 'c')
				{
					fputc(va_arg(more_args, int),stdout);
					i++;
				}
				else if(format[i+1] == 's')
				{
					character_array = (char*)va_arg( more_args, char*);
					while(character_array[j] != '\0')
					{
						fputc(character_array[j], stdout);
						j++;
					}
					i++;
				}
				else if(format[i+1] == 'x')
				{
					print_integer(va_arg(more_args, int), 16, "0x");
					i++;
				}
				else if (format[i+1] == 'b')
				{
					print_integer(va_arg(more_args, int), 2, "0b");
				 	i++;
				}
				else if(format[i+1] == '$')
				{
					double val_d = va_arg(more_args, double);
					double copy_val_d = val_d;
					if( val_d < 0)
					{
						val_d *= -1;
					}
				    unsigned int val_i = (unsigned int)val_d;
					true_val = (val_d - val_i)*100;
					if(copy_val_d < 0)
					{
						fputc('-', stdout);
					}
					print_integer(val_i, 10, "$");
					fputc('.', stdout);
					if(true_val < 10)
					{
						fputc('0', stdout);
					}
					print_integer(true_val, 10, "");
					i++;
				}
				else if(format[i+1] == '%')
				{
					fputc('%', stdout);
					i++;
				}
				else
				{
					fputc(format[i], stdout);
				}
		}
		i++;
	}
}

	


	


	


#include<stdio.h>
#include<stdlib.h>
#include<stdarg.h>
#include"mintf.h"

int main(int argc,char *argv[])
{	
//	int i= 241;
	mintf("12512\n");
	mintf("The integer is %d!\n", 151);
	mintf("%d is written as %x in hexadecimal\n", 20, 20);
    mintf("%d is written as %b in binary\n", 51, 51);
	mintf("I got an 84% in my ECE homework\n");
	mintf("I got an 84%% in my ECE homework\n");
	mintf("%s is a dog with %d bones\n", "Bernard", 20);
	mintf("She has %$ dollars in her bank\n", 25.024);
	mintf("Why is this not working? %$  %% lsdfsdf\n", -80.3341512 );
	mintf("Why is this not working? %$  %% lsdfsdf\n", 80.00000 );
	mintf("What happens with too many %s", "arguments\n", 2415, "C");
	mintf("the wrong specifier gives %z", 251);
}

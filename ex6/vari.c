#include "stdio.h"
int main(int argc, char *argv[])
{
	int distance = 100;
	float power = 2.345f;
	double supper_power = 56789.5432;
	char initial = 'A';
	char first_name[] = " ";
	char last_name[] = "Shaw";

	printf("You are %x miles away .\n",distance);
	printf("You have %f levels of power. \n",power);
	printf("You have %f awesome super powers.\n",supper_power);
	printf("I nave a first name %s \n",first_name);
	printf("My whole name is %s %c. %s \n",first_name, initial,last_name);
	return 0;

}

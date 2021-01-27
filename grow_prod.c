
#include <stdio.h>
int main()
{
	int num_1 = 0;
	int num_2 = 0;
	int num_3 = 0;
	int prod = 0;
	printf("Enter first integer: ");
	scanf("%d", &num_1);
	printf("Enter second integer: ");
	scanf("%d", &num_2);
	prod = num_1*num_2;
	printf("Enter another integer: ");
	scanf("%d", &num_3);
	while (num_3 > prod)
	{
		prod = num_2*num_3;
		num_2 = num_3;
		printf("Enter another integer: ");
		scanf("%d", &num_3);
	}
	return 0;
}

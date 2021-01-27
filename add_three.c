# include <stdio.h>
int main()
{
	int num_1 = 0;
	int num_2 = 0;
	int num_3 = 0;
	printf("Enter first integer: ");
	scanf("%d", &num_1);
	printf("Enter second integer: ");
	scanf("%d", &num_2);
	printf("Enter third integer: ");
	scanf("%d", &num_3);
	int result = num_1 + num_2 + num_3;
	printf("The sum is: %d\n", result);
	return 0;
}

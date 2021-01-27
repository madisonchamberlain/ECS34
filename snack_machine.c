#include <stdio.h>
int main()
{
	char character = 'a';
	float money = 0.00;
	printf("Machine currently has $0.00 in it.\n");
	while (character != 's')
	{
		printf("Enter: ");
		scanf(" %c",&character);
		switch(character)
		{
			case 'q':
				 money = money + 0.25;
				 printf("Machine currently has $%.2f in it.\n", money);
				 break;
			case 'd':
				 money = money + 0.10;
				 printf("Machine currently has $%.2f in it.\n", money);
				 break;
			case 'n':
				money = money + 0.05;
				printf("Machine currently has $%.2f in it.\n", money);
				break;
			case 'p':
				money = money + 0.01;
				printf("Machine currently has $%.2f in it.\n", money);
				break;
			case 's':
				 printf("Have a nice day.\n");
				 return 0;
				 break;
			case 'l':
				 if (money >= 2.00)
				 {
					 money = money - 2.00;
					 printf("Enjoy your Lay's chips.\n");
					 printf("Machine currently has $%.2f in it.\n", money);
				 }
				 else 
				 {
					 float difference = 2.00 - money;
					 printf("You need $%.2f more to afford Lay's chips.\n", difference);
					 printf("Machine currently has $%.2f in it.\n", money);
				 }
				 break;
			case 'r':
				 if (money >= 2.25)
				 {
					 money = money - 2.25;
					 printf("Enjoy your Ruffles chips.\n");
					 printf("Machine currently has $%.2f in it.\n", money);
				 }
				 else 
				 {
					 float difference = 2.25 - money;
					 printf("You need $%.2f more to afford Ruffles chips.\n", difference);
					 printf("Machine currently has $%.2f in it.\n", money);
				 }
				 break;
			case 'k':
				 if (money >= 1.50)
				 {
					 money = money - 1.50;
					 printf("Enjoy your Kit Kat candy.\n");
					 printf("Machine currently has $%.2f in it.\n", money);
				 }
				 else 
				 {
					 float difference = 1.50 - money;
					 printf("You need $%.2f more to afford a Kit Kat.\n", difference);
					 printf("Machine currently has $%.2f in it.\n", money);
				 }
				 break;
			default:
				 printf("Invalid input.\n");
				 printf("Machine currently has $%.2f in it.\n", money);
				 break;
		}
	}
}	

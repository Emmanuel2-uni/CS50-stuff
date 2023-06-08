#include <stdio.h>
//testing CS50x style convention\
//  https://cs50.readthedocs.io/style/c/
//my rudimentary solution to their mario exercise but in c++

int height;
int row=0;


int main(){
	
	printf("Input height of pyramid: ");
	scanf("%i", &height);
	
	printf("%i\n", height);
	
	do
	{
		row++;
		for (int space = 0; space < (height-row); space++)
			{
				printf(" ");
			}
			
		for (int left = 0; left < row; left++)
			{
				printf("#");
			}
			
		printf(" ");
		
		for (int right = 0; right < row; right++)
			{
				printf("#");
			}		
			
		printf("\n");
	}
	while(row!=height);
	
	
	printf("\n");

	
	return 0;
}
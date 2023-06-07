#include <iostream>
//testing CS50x style convention\
//  https://cs50.readthedocs.io/style/c/
//my rudimentary solution to their mario exercise but in c++

int height;
int row=0;


int main(){
	
	std::cout << "Input height of pyramid: ";
	std::cin >> height;
	
	std::cout << std::endl;


	do
	{
		row++;
		for (int space = 0; space < (height-row); space++)
			{
				std::cout << " ";
			}
			
		for (int left = 0; left < row; left++)
			{
				std::cout << "#";
			}
			
		std::cout << " ";
		
		for (int right = 0; right < row; right++)
			{
				std::cout << "#";
			}		
			
		std::cout << std::endl;
	}
	while(row!=height);
	
	
	std::cout << std::endl;
	
	return 0;
}

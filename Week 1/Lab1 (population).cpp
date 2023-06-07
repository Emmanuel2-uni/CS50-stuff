#include <iostream>

int start_size = 0;
int end_size = 0;
int current_size = 0;
int year = 0;
int choice = 0;
bool run = true;

int main()
{
	
	while(run==true)
	{
		do
		{
			system("CLS");
			std::cout << "Enter starting size: ";
			std::cin >> start_size;
		
		}
		while(start_size<9);


		do
		{
			system("CLS");
			std::cout << "Starting size: " << start_size;
			std::cout << "\nEnter ending size: ";
			std::cin >> end_size;
		
		}
		while(end_size<start_size);
	
	
		current_size = start_size;
		year=0;
	
		do
		{
			year++;
			current_size = current_size + (current_size/3) - (current_size/4);
		
		}
		while(current_size<end_size);
	
		std::cout << "\nYears it will take: " << year;
		
		std::cout << "\nPredict new population data? [1-Yes | 2-No]: ";
		std::cin >> choice;
		if ( choice==2 )
		{
			run=false;
		}
	}

	
}
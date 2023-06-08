#include <iostream>

// Optional problem from CS50x Week 1
//  https://cs50.harvard.edu/x/2023/problems/1/prime/


bool prime(int number);
int start_number;
int end_number;


int main()
{
	std::cout << "Enter starting number: ";
	std::cin >> start_number;
	
	std::cout << "Enter ending number: ";
	std::cin >> end_number;
	
	std::cout << std::endl;
	
	
	for(int number = start_number; number <= end_number; number++)
	{
		// If the boolean function prime() returns true, then it prints the value stored in the number variable according to the current for-loop.
		if ( prime(number)==true )
		{
			std::cout << number << std::endl;
		}	
	}
	
	return 0;
}


bool prime(int number)
{
	// The practice problem asks for a boolean function.
	// Therefore we need to return a boolean/truth value.
	int current_number = number;
	bool prime_flag = true;
	
	
	// The code below will check if the current number is divisible (AKA modulo/remainder is 0) by specific numbers starting from 2 up to current number minus 1.
	// Example: 121 is not divisible by 2, 3, 5, 7 but is divisible by another prime number: 11.
	for (int check = 2 ; check < current_number; check++)
	{
		if ( current_number%check==0 )
		{
			prime_flag=false;
		}	
	} 
	
	
	// Special case for 1
	if (number == 1)
	{
		prime_flag = false;
	}
	
	
	return prime_flag;
	
}
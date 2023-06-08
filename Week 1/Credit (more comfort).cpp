#include <iostream>
#include <cmath>
// Testing CS50x style convention\
//  https://cs50.readthedocs.io/style/c/
// My rudimentary solution to their credit card exercise but in c++
//  https://cs50.harvard.edu/x/2023/psets/1/credit/


void get_card();
int get_checksum();
std::string check_validity(int checksum);
std::string get_card_issuer();

long long card_number;
long long digit;
bool run = true;
int choice = 0;


int main()
{
	do{
		system("CLS");
		int checksum = 0;
	
		get_card();
		
		std::cout << "\nCard number: " << card_number;
		//std::cout << "\n\nCHECKSUM: " << get_checksum();
	
		checksum = get_checksum();
	
		std::cout << "\nCard Validity: " << check_validity(checksum);
		std::cout << "\nIssuer: " << get_card_issuer();
		std::cout << "\n\nCheck a different card? [1-Yes | 2-No] ";
		std::cin >> choice;
			if (choice==2){
				run=false;
			}
	}while(run==true);
	
	return 0;
}


void get_card()
{
	std::cout << "Input card number: ";
	std::cin >> card_number;	
	
}

int get_checksum()
{
	long long remainder;
	long long digit_place = 0;
	long long card_number_backup = card_number;
	int checksum_product = 0;
	int checksum_noproduct = 0;
	int checksum;
	
	int digit_product;
	
	do
	{
		digit_place++;
		
		// Using the modulo operation to determine the last digit.
		digit = card_number_backup % (10);
		
		// Debug line below for following the digit place.
		// std::cout << "\n\nDigit " << digit_place << " :" << digit;
		
		// As detailed in the problem set's webpage, the first step is to determine the number in every other digit starting from the right.
		// Example: 4003600000000014
		// Every other number from right to left: 1 0 0 0 0 6 0 4
		
		// Read from right to left, where the rightmost digit is the first digit; using modulo operation to determine if the digit's place is even.
		if ((digit_place%2)==0)
		{
			// If it is found that it the digit's place is even, we multiply that specific digit by 2 as per the mentioned algorithm.
			digit_product = digit*2;
			
			// Debug line for checking digit place and current number.
			// std::cout << "\nCurrent digit product: " << digit_product;
			
			do
			{	
				
				// After multiplying the digit by 2, we then add the digits of the product.
				// Example: 6 * 2 = 12
				// Therefore we add 1 + 2 = 3.
				// Using modulo we can determine the first and second digits of the product. 12 % 10 = 2 and 1 % 10 = 1.
				// We divide by 10 in order to remove the right most digit. 12/10 = 1  then 1/10 = 0.
				checksum_product += (digit_product % 10);
				
				// Remove comment from the cout below to debug checksum products;
				// std::cout << "\nAdding " << digit_product % 10 << " from " << digit_product;
				// std::cout << "\nCurrent Checksum: " << checksum_product;
			
				digit_product = digit_product / 10;
				
			}while(digit_product!=0);
			
			
		}
		else if ((digit_place%2)!=0)
		{
			// Debug line below for checking which digit is being called by the if condition.
			// std::cout << "\nDigit: " << digit;
			
			checksum_noproduct += digit;
			
		}
	
		// Using the integer data type and dividing by 10, we can cut the last digit out without any floating remainders.
		remainder = card_number_backup / 10;
		
		// std::cout << "\n  Remaining digits: " << remainder;
		
		card_number_backup = remainder;
		
	}
	while(card_number_backup!=0);
	
	checksum = checksum_product + checksum_noproduct;
	
	return checksum;
	
}


std::string get_card_issuer()
{
	// American Express uses 15-digit numbers (starts with 34 or 37) 
	// MasterCard uses 16-digit numbers (starts with 51 to 55) 
	// And Visa uses 13- and 16-digit numbers (starts with 4)
	
	
	long long card_number_backup = card_number;
	long long remainder = card_number;
	int digit_count=0;
	int first_digit=0;
	int second_digit=0;
	std::string issuer;
	
	do
	{
		// Determines the number of digits that the card has.
		digit_count++;
		remainder = remainder / 10;
	}
	while(remainder!=0);
	
	
	switch (digit_count)
	{
		case 16:
			// Determine last digit if there are 16 numbers on the card
			first_digit = card_number_backup / pow(10,15);
			second_digit = (card_number_backup / pow(10,14));
			second_digit = second_digit%10;
			
			if ( first_digit == 4 )
			{
				issuer = "VISA";
			}
			else if ( first_digit == 5 && (second_digit >= 1 || second_digit <= 5) )
			{
				issuer = "MasterCard";
			}
			else
			{
				issuer = "Invalid card number.";
			}
			
			// Debug lines below for checking first and second digit;
			// std::cout << "\nFirst digit: " << first_digit;
			// std::cout << "\nSecond digit: " << second_digit;
			
			break;
			
			
		case 13:
			first_digit = card_number_backup / pow(10,12);
			
			if ( first_digit == 4 )
			{
				issuer = "VISA";
			}
			else
			{
				issuer = "Invalid card number.";
			}		
				
			break;
		
		//first_digit == 5 && (second_digit <= 5 || second_digit >= 1)
		
		case 15:
			first_digit = card_number_backup / pow(10,14);
			second_digit = (card_number_backup / pow(10,13));
			second_digit = second_digit%10;
			
			if ( first_digit == 3 && (second_digit == 4 || second_digit == 7) )
			{
				issuer = "American Express";
			}
			else
			{
				issuer = "Invalid card number.";
			}
			break;
			
			
		default:
			issuer = "Invalid card number.";
			break;
			
			
	}
	
	return issuer;
	
}


std::string check_validity(int checksum)
{
	std::string validity;
	
	if ( checksum % 10 == 0 )
	{
		validity = "Valid.";
	}
	else if ( checksum % 10 != 0 )
	{
		validity = "Invalid.";
	}
	
	return validity;
}

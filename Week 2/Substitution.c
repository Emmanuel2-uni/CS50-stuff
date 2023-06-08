#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

bool check_key(char ciph_key[]);
char lower_key(char text[]);
void encrypt_text(char ciph_key[]);

char orig_key[27] = {"ABCDEFGHIJKLMNOPQRSTUVWXYZ"};
char ciph_key[27];
char text[50];
char cipher[50];



int main(void)
{
	// Example crypt key: YTNSHKVEFXRBAUQZCLWDMIPGJO
	
	printf("Input key: ");
	
	// Similar to getline in C++
	fgets(ciph_key, 27, stdin);

	// Debug lines below
	// scanf("%s", ciph_key);
	// printf(ciph_key);
	
	lower_key(ciph_key);
	
	if(check_key(ciph_key)==false)
	{
		return main();	
	}

	printf("\nInput text: ");
	// IT TAKES TWO LINES TO REPLICATE cin.ignore() REEEEEEEEE
	// Credit: https://stackoverflow.com/questions/2187474/i-am-not-able-to-flush-stdin-how-can-i-flush-stdin-in-c
	int c;
	while ( (c = getchar()) != '\n' && c != EOF );
	
	fgets(text, 50, stdin);
	
	printf("\nPlain text:  %s", text);
	encrypt_text(ciph_key);
	
	printf("\nCipher text: %s", cipher);
	
	
	return 0;
}




char lower_key(char ciph_key[])
{
	for(int i=0; i < strlen(ciph_key); i++)
	{
		ciph_key[i] = tolower(ciph_key[i]);
		orig_key[i] = tolower(orig_key[i]);
	}
}


bool check_key(char ciph_key[])
{
	bool validity = true;
	
	// First, we check the length of the cipher key. If it's not 26, we return to main();
	if(strlen(ciph_key)!=26)
	{
		validity = false;
	}
	
	
	// Second, we check each character of the key to see if it's an alphabet.
	for(int i = 0; i < strlen(ciph_key); i++)
	{
		if(!isalpha(ciph_key[i]))
		{
			validity = false;
		}
		
	}
	
	
	// Third, we check if it contains a copy of the same character.
	for (int i = 0; i < strlen(ciph_key); i++)
	{
		// Since we don't need to compare the same character to itself, we adjust the index j to the next of i.
		// Example: key[0] will then be compared to key[1].
		for(int j = i+1; j < strlen(ciph_key); j++)
		{
			if(ciph_key[i]==ciph_key[j])
			{
				validity = false;
			}
		}
	}
	
	return validity;
		
}

void encrypt_text(char ciph_key[])
{
	char text_backup[50];
	strcpy(text_backup, text);
	
	// We make a backup of the original text just in case we need them.
	for(int i=0; i < strlen(text); i++)
	{
		text[i] = tolower(text[i]);
	}
	
	// First, we check each letter of the text that user has input.
	for(int i = 0; i < strlen(text); i++)
	{
		
		// Second, we will then compare each letter of that text with the original ordering of the alphabet (ABCDE...)
		for(int letter = 0; letter < 26; letter++)
		{
			// Once we've found letter's original position in the alphabet, we will then replace it with the cipher key with the same position.
			// If the letter is not a letter, aka it's a number or a symbol, we simply copy it.
			if( text[i]==orig_key[letter] )
			{
				cipher[i] = ciph_key[letter];
			}
			else if(!isalpha(text[i]))
			{
				cipher[i] = text[i];
			}
			
			// If it's found that the original text has an uppercase letter, we will simply capitalize the one in the encrypted text.
			if(isupper(text_backup[i]))
			{
				cipher[i] = toupper(cipher[i]);
			}
				
		}
	}
	
	
	
}
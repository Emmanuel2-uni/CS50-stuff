#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int letter_count(char text[]);
int word_count(char text[]);
int sentence_count(char text[]);
float find_index(char text[]);

// index = 0.0588 * L - 0.296 * S - 15.8
// L is the number of letters per 100 words
// S is the number of sentences per 100 words.	

int main(void)
{
	
	// fgets is used in order to count spaces.
	char text[700];
	printf("Input text: ");
	fgets(text, 700, stdin);

	// These are effectively Debug lines (line 22 to 29) to help find out if words/sentences/letters are being counted correctly.
	int letters = letter_count(text);
	int words = word_count(text);
	int sentences = sentence_count(text);
	
	printf("Letters: %i", letters );
	printf("\nWords: %i", words );
	printf("\nSentences: %i", sentences );
	
	// Function to find the index.
	float index_result = round(find_index(text) );
	
	// Rudimentary solution for grade classification.
	if ( index_result>=16)
	{
		printf("\nGrade 16+");
	}
	else if ( index_result < 1)
	{
		printf("\nBefore Grade 1");
	}
	else
	{
		printf("\nGrade %.f", index_result);	
	}
	
}


int letter_count(char text[])
{
	int letter_count = 0;
	
	for(int i = 0; i < strlen(text); i++)
	{
		if(!isspace(text[i]) && isalpha(text[i]))
		{
			letter_count++;
		}	
	}
	
	return letter_count;
	
}



int word_count(char text[])
{
	int word_count = 0;
	
	for(int i = 0; i < strlen(text); i++)
	{
		if(isspace(text[i]))
		{
			 word_count++;	
		}
	}	
	
	return word_count;
	
}

int sentence_count(char text[])
{
	int sentence_count = 0;
	
	for(int i = 0; i < strlen(text); i++)
	{
		if(text[i] == '.' || text[i] == '!' || text[i] == '?' )
		{
			 sentence_count++;	
		}
	}	
	
	return sentence_count;
}

float find_index(char text[])
{
	float index_L;
	float index_S;
	float index_result;
	
	// These cannot be of int data types. I tried and it failed to calculate properly. These must be float too.
	float word_count = 0;
	float sentence_count = 0;
	float letter_count = 0;
	
	for(int i = 0; i < strlen(text); i++)
	{
		if(isspace(text[i]))
		{
			 word_count++;	
		}
		
		if(text[i] == '.' || text[i] == '!' || text[i] == '?' )
		{
			 sentence_count++;	
		}
		
		if(!isspace(text[i]) && isalpha(text[i]))
		{
			letter_count++;
		}
			
	}	
	
	// index = 0.0588 * L - 0.296 * S - 15.8
	// L is the number of letters per 100 words
	// S is the number of sentences per 100 words.	
	index_L = (letter_count / word_count) * 100;
	
	index_S = (sentence_count / word_count) * 100;
	
	// Debug lines for checking if index variables are calculated properly.
	// printf("\nIndex L: %f", index_L);
	// printf("\nIndex S: %f", index_S);

	index_result = 0.0588 * index_L - 0.296 * index_S - 15.8;
	
	return index_result;
	
}

#include <ctype.h>
//#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet, provided by CS50
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

// Since the course already provided the points, we just need to make another array that contains the original alphabet.
// The indexes already match; A being 0 correspond to 1 point (POINTS[0]), Z being 25 correspond to 10 points (POINTS[25]).
char orig_alphabet[] = {"ABCDEFGHIJKLMNOPQRSTUVWXYZ"};

int compute_score(char word[]);

char word1[15];
char word2[15];

int main(void)
{
    // Get input words from both players
    // string word1 = get_string("Player 1: ");
    // string word2 = get_string("Player 2: ");
	
	// We get the inputs from the two players using fgets().
	printf("Player 1: ");
	fgets(word1, 15, stdin);
	
	printf("Player 2: ");
	fgets(word2, 15, stdin);


	//Debug line below, show the current word.
	printf("\nPlayer 1's word: %s", word1);
	printf("Player 2's word: %s", word2);
	
	
    // Score both words, provided by CS50
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // TODO: Print the winner
    // Rudimentary solution.
    if (score1 > score2)
    {
    	printf("\nPlayer 1 wins with a score of %i", score1);
    }
    else if (score2 > score1)
    {
	printf("\nPlayer 2 wins with a score of %i", score2);
    }
	
	
}

// Function name provided by CS50, code made by me.
int compute_score(char word[])
{
	int score = 0;
	
    for(int i = 0; i < strlen(word); i++){
    	
    	// This will allow us to make the text case uniform for computation purposes.
    	word[i] = toupper(word[i]);
		
		for(int j = 0; j < strlen(orig_alphabet); j++)
		{
			// If the letter in the word is found in the original alphabet, then it will add the corresponding POINTS according to its index.
			if( word[i] == orig_alphabet[j])
			{
				score += POINTS[j];
			}
		}	
	}
    
    return score;
}

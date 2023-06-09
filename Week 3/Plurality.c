//#include "cs50.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
	// Nine candidates maximum.
    char name[50];
    int votes;
}
candidate;

typedef struct
{
	char name[50];
	int votes;
}
winner;

// Array of candidates, declare using the candidate struct
candidate candidates[MAX];
winner winners[MAX];


// Number of candidates
int candidate_count;

// Function prototypes
bool vote(char name[], int candidate_count);
void print_winner(int candidate_count);


// Function to clear input stream, similar to cin.ignore() in C++.
void clearstream();


int main(void)
{
    // Populate array of candidates
    char input[50];
    
    printf("Input candidate count: ");
    fgets(input, 50, stdin);
    int candidate_count = atoi(input);
    printf("\nCandidate count: %i\n", candidate_count);
    
    
    
    if (candidate_count > MAX || candidate_count < 2)
    {
        printf("\nMaximum number of candidates is %i. || Minimum is 2.\n", MAX);
        system("PAUSE");
        system("CLS");
        return main();
    }
    
    for (int i = 0; i < candidate_count; i++)
    {
    	printf("Input candidate %i name: ", i+1);
    	
    	fgets(input, 50, stdin);
        strcpy(candidates[i].name, input);    
        candidates[i].votes = 0;
       
    }

	printf("\n");
	
	// Debug lines for checking candidate names
	/*
	for (int i = 0; i < candidate_count; i++)
	{
		printf("Candidate %i: %s", i+1, candidates[i].name);
	}
	*/


	printf("\nInput number of voters: ");
    fgets(input, 50, stdin);
    int voter_count = atoi(input);
    printf("\nVoter count: %i", voter_count);
    
    bool flag;
    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
    	printf("\nVoter %i: ", i+1);
      
		fgets(input, 50, stdin);
		
        // Check for invalid vote
    	
    	flag = vote(input, candidate_count);
    	if(flag==false)
		{
    		printf("Invalid vote.\n");
		}
    	//if(vote(input, candidate_count)true);
       // {
        //   printf("Invalid vote.\n");
		//}
    }
    
    // Display winner of election
    print_winner(candidate_count);
}


// Update vote totals given a new vote
bool vote(char name[], int candidate_count)
{
    // TODO - Done
    bool flag=false;
    
    // Candidate count is NOT a global variable
    for(int i = 0; i < candidate_count; i++)
    {
    	if( strcmp(candidates[i].name, name) == 0)
    	{
    		candidates[i].votes++;
    		flag=true;
		}
	}
	
	return flag;
	
}

// Print the winner (or winners) of the election
void print_winner(int candidate_count)
{
    // TODO - Done
    
    // Sorting algorithm to determine the winner/winners.
    for(int i = 0; i < candidate_count; i++)
    {
    	
    	for(int j = i; j < candidate_count; j++)
    	{
    		if(candidates[i].votes <= candidates[j].votes)
    		{
    			strcpy(winners[i].name, candidates[j].name);
    			strcpy(candidates[j].name, candidates[i].name);
    			winners[i].votes = candidates[j].votes;
    			candidates[j].votes = candidates[i].votes;
			}
		}
		
	}
	
	// Debug line to check winners and their votes.
	/*
	for(int i = 0; i < candidate_count; i++)
	{
		printf("%s %i\n", winners[i].name, winners[i].votes);
	}
	*/

	printf("\nWinners: \n");
	//printf("%s", winners[0].name);
	for(int i = 0; i < candidate_count; i++)
	{
		if(winners[i].votes==winners[0].votes)
		{
			printf(" %s", winners[i].name);
		}
	}
    return;
}



void clearstream()
{
	int c;
	while ( (c = getchar()) != '\n' && c != EOF );	
}
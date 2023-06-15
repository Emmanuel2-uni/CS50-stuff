//#include "cs50.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX] = {false};
bool found_pair[MAX][MAX] = {false};

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;


typedef struct
{
	char name[50];
}
candidate;

// Array of candidates
candidate candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];


int pair_count;
int candidate_count;
int node_strength[MAX] = {0};

// Function prototypes
bool vote(int rank, char name[], int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
bool cycle_found = false;

void check_cycles(bool node_found[], bool finished[], int node);
void check_winner(bool node_found[], bool finished[], int node, int source);


// Debug functions
void check_candidates();
void check_pairs();


int main(void)
{
	char input[50];
	
    // Check for invalid usage
    //if (argc < 2)
    //{
    //   printf("Usage: tideman [candidate ...]\n");
    //    return 1;
   	//}

    // Populate array of candidates
    //candidate_count = argc - 1;
    //if (candidate_count > MAX)
    //{
    //    printf("Maximum number of candidates is %i\n", MAX);
    //    return 2;
    //}
    //for (int i = 0; i < candidate_count; i++)
    //{
    //    strcpy(candidates[i].name, argv[i + 1]);
    //}
    
    printf("Input candidate count: ");
    fgets(input, 50, stdin);
    candidate_count = atoi(input);
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
       
    }

	printf("\n");
    

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }


    pair_count = 0;
    pair_count = (candidate_count * (candidate_count-1) / 2);
    ///////////////////// redo without cs50.h
    // int voter_count = get_int("Number of voters: ");
    
	printf("\nNumber of voters: ");
	fgets(input, 50, stdin);
	int voter_count = atoi(input);
	
	int rank;
    // Query for votes
    bool flag;
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];
        
		printf("Voter 1 ranks: \n");
		
        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
        	
        	//////////////////////// redo
            //string name = get_string("Rank %i: ", j + 1);
            
            printf("Rank %i: ", j+1);
            fgets(input, 50, stdin);
    
                        
            // ranks[j] = candidate_count - j;
            // rank 1: ranks[0] = 2-0 == strength = 2;
            // rank 2: ranks[1] = 2-1 == strenght = 1;
            
			flag = vote(j, input, ranks);
			
            if (flag==false)
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }
		
        printf("\n");
		record_preferences(ranks);
		
		// Debug line for checking preference values
		//check_candidates();
		
		
        printf("\n");
    }

    add_pairs();
    // Debug function for checking pairs.
    check_pairs();
    printf("\nPairs checked.\n");
    
    sort_pairs();
    
    // Print it again to see if things were sorted correctly.
    printf("Sorted: \n");
    check_pairs();
    
    lock_pairs();
    print_winner();
    return 0;
}


// Update ranks given a new vote
bool vote(int rank, char name[], int ranks[])
{
    // TODO
    bool flag=false;
    
    for(int i = 0; i < candidate_count; i++)
    {
		if(strcmp(name, candidates[i].name)==0)
		{
			// Example: Once a name is found,
			// index i (candidate A or index 0 in the candidates struct for example) becomes the 0th [passed over from the j value in main()] preference rank a.k.a the first rank.
			// THIS SINGLE LINE OF CODE TOOK ME AN HOUR TO FIGURE OUT ASDJKJQWBEOUIWQEH
			ranks[rank] = i;
			
			flag=true;
		}	
	}
    
    return flag;
}


// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // TODO
    // preferences[i][j] is number of voters who prefer i over j
	// int preferences[MAX][MAX];
	// Example:
	// Ranks - Candidates(candidate index)
	// 0 - B(1)
	// 1 - A(0)
	// 2 - C(2)
	// Preferences to be updates should be:
	// pref[1][0]++
	// pref[1][2]++
	// pref[0][2]++
	// put it on paper and observe?
	
	
    for(int i = 0; i < candidate_count-1; i++)
	{
		// Debug line to see up to where the code is being called
		// printf("AAA%i", i);
		
		for(int j = i+1; j < candidate_count; j++)
		{	
			// printf("AAAA");
			// Assume ranking: B A C
			// i j Names
			// 0 1	B A
			// 0 2	B C
			// 1 2	A C
		
			if(i==j)
			{
				// This is to effectively "skip" the indexes if they are equal to each other.
			}
			else
			{
				// Debug line to see up to where the code is being called
				// printf("BBB%i", j);
				preferences[ranks[i]][ranks[j]] += 1;
			}

			
		}
		
	}
    
    
    // Debug lines below for checking candidate rank
    /*
	for(int i = 0; i < candidate_count; i++)
    {
    	printf("\nCandidate %i %s Rank %i\n", i+1, candidates[i].name, ranks[i]);
	}
    return;
    */
    
}


// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO
    // Note to self: preferences[i][j] is a global variable
	int count = pair_count;
	int count_pair = 0;
	 

    for(int i = 0; i < candidate_count; i++)
    {
    	for(int j = i+1; j < candidate_count; j++)
    	{
    		if( (preferences[i][j] - preferences[j][i]) > 0)
    		{
    			//strcpy(pairs[count_pair].winner, candidates[i].name);
    			//strcpy(pairs[count_pair].loser, candidates[j].name);
    			
    			pairs[count_pair].winner = i;
    			pairs[count_pair].loser = j;
    			count_pair++;
			}
			else if ( (preferences[i][j] - preferences[j][i]) < 0)
			{
				
    			pairs[count_pair].winner = j;
    			pairs[count_pair].loser = i;
    			count_pair++;
			}
			else
			{
				
			}
		}
	}
    
    // Please do not do this kind of variable naming. My dumb ass is just too lazy.
    pair_count = count_pair;
    
    
    // Debug line for checking total pair count;
    /*
	printf("\nTotal pairs: %i", count_pair);
    for(int i = 0; i < pair_count; i++)
		{
			printf("\nWinner: %i", pairs[i].winner);
			printf("\nLoser: %i", pairs[i].loser);
		}	
	
    return;
    */
}


// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
	// TODO
	
	int pair_strength[pair_count];
	int backup_strength;
	int backup_winner;
	int backup_loser;
	
	
	// Calculate pair strength
	for(int i = 0; i < pair_count; i++)
	{
			pair_strength[i] = preferences[pairs[i].winner][pairs[i].loser] - preferences[pairs[i].loser][pairs[i].winner];
			printf("Pair %i strength: %i\n", i, pair_strength[i]);
			
	}
	
	for(int i = 0; i < pair_count; i++)
	{
		for(int j = i; j < pair_count; j++)
		{
			if(pair_strength[i] < pair_strength[j])
			{
				backup_strength = pair_strength[i];
				pair_strength[i] = pair_strength[j];
				pair_strength[j] = backup_strength;
				
				
				backup_winner = pairs[i].winner;
				backup_loser = pairs[i].loser;
				
				pairs[i].winner = pairs[j].winner;
				pairs[j].winner = backup_winner;
				
				pairs[i].loser = pairs[j].loser;
				pairs[j].loser = backup_loser;
				
			}
		}
	}
	
	
    return;
}


void check_cycles(bool node_found[], bool finished[], int node)
{
	
	if(finished[node] == true)
	{
		return;
	}
	
	if(node_found[node]==true)
	{
		printf("\nCycle found.\n");
		cycle_found = true;
		return;
	}
	
	node_found[node] = true;
	
	for(int i = 0; i < candidate_count; i++)
	{
		if(locked[node][i] == true)  //&& finished[i] == false) //&& node_found[i] == false)
		{
			check_cycles(node_found, finished, i);	
		}
	}
	
	finished[node] = true;
	
	
	// References:
	// https://en.wikipedia.org/wiki/Cycle_(graph_theory)#See_also
	// https://en.wikipedia.org/wiki/Depth-first_search#Output_of_a_depth-first_search
	// 
	// See also:
	// How Recursion works
	
}

void check_winner(bool node_found[], bool finished[], int node, int source)
{
	
	if(finished[node] == true)
	{
		node_strength[source]++;
		return;
	}
	
	node_found[node] = true;
	
	
	for(int i = 0; i < candidate_count; i++)
	{
		if(locked[node][i] == true)  //&& finished[i] == false) //&& node_found[i] == false)
		{
			check_winner(node_found, finished, i, source);	
		}
		
	}
	
	finished[node] = true;
	node_strength[source]++;
	
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO
    // locked[i][j] means i is locked in over j
	// bool locked[MAX][MAX];
	bool flag = false;
	
	
	for(int i = 0; i < pair_count; i++)
	{
		locked[pairs[i].winner][pairs[i].loser] = true;
		printf("\nPair %i locked.", i);
		
		bool node_found[MAX] = {false};
		bool finished[MAX] = {false};
		cycle_found = false;
		
		check_cycles(node_found, finished, pairs[i].winner);
		
		if( cycle_found == true)
		{
			printf("\nPair %i unlocked.", i);
			locked[pairs[i].winner][pairs[i].loser] = false;
		}
		
	}
}


// Print the winner of the election
void print_winner(void)
{
    // TODO
    
    for(int i = 0; i < candidate_count; i++)
	{
    	bool node_found[MAX] = {false};
		bool finished[MAX] = {false};
		int source = i;
		
		check_winner(node_found, finished, i, source);
	}
    
    // Debug line for checking each of the sources'/nodes' strength
    for(int i = 0; i < candidate_count; i++)
    {
    	printf("\nNode %i: %i", i, node_strength[i]);
	}
    
    int winner = 0;
    
    for(int i = 0; i < candidate_count; i++)
	{
    		if(node_strength[winner] < node_strength[i])
    		{
    			//0, 2, 5, 3
    			winner = i;
			}	
	}
	
	printf("\n\nWinner: %s", candidates[winner].name);
	
    return;
}

/////
// Debug functions below
void check_candidates()
{
	for(int i = 0; i < candidate_count; i++)
		{
			for(int j = 0; j < candidate_count; j++)
			{
				if(i==j)
				{
					// To skip
				}
				else
				{
					printf("Preference %i%i: %i\n", i, j, preferences[i][j]);
				}
			}	
		}
}

void check_pairs()
{
	for(int i = 0; i < pair_count; i++)
		{
			printf("\nPair %i", i+1);
			
			printf("\nWinner: %s", candidates[pairs[i].winner].name);
			printf("Loser: %s", candidates[pairs[i].loser].name);
		}	
}


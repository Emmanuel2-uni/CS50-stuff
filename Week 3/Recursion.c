#include <stdio.h>

void draw(int n);

int main(void)
{
    // Get height of pyramid
    int height = 5;

    // Draw pyramid
    draw(height);
}

void draw(int n)
{
    // If nothing to draw
    if (n <= 0)
    {
        return;
    }
    
	// Added print line to observe behaviour.
	printf("B");
	
	//
	// Personal Notes using CS50's recursion example:
	// It seems that there is a "stack" of sorts. 
	// Printf("B") will get called five times initially before the first printf("AAA")
	// this means that draw(n-1) keeps getting called
	// however, after n is equal to 0 (as per the terminating condition n <= 0), the first row is a single # instead of my expected #####
	// I think recursion is applied through a stack? where the last called function 
	// in this case draw(1) is called first and the last function to be executed is the first one: draw(5).
	//
	
    // Draw pyramid of height n - 1
    draw(n - 1);
	
	// Added print line to observe behaviour.
	printf("AAA");
	
	
    // Draw one more row of width n
    for (int i = 0; i < n; i++)
    {
        printf("#");
    }
    printf("\n");
    
    // Added recursive function line to observe behaviour.
    // draw(n-1);
    
    //draw(n - 1);
}
#include <stdio.h>
#include <cs50.h>

//argc == argument counter 
//argv == argument vector/list (stores all strings typed in the prompt while the program is running)
int main (int argc, string argv[])
{
	if (argc >= 2)
	{
		printf("hello, %s\n", argv[1]);
	}
	else
	{
		printf("hello, world");
	}
	
}

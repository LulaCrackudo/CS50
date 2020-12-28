#include <stdio.h>
#include <cs50.h>

void draw(int h);

int main (void)
{
	int height;
	do
	{
		height = get_int("Altura: ");
	} while (height <= 0 || height > 8);
	draw(height);
	return 0;
}

void draw(int h){
	for (int i = 0; i < h; i++){ // iterates over each row
		for (int spaces = (h - i); spaces >= 0; spaces--){
			printf(" ");
		}
		for (int dashes = 0; dashes < (i + 1); dashes++){
			printf("#");    
		}
		printf("  ");
		for (int dashes = 0; dashes < (i + 1); dashes++){
			printf("#");    
		}
		printf("\n");
	}
}
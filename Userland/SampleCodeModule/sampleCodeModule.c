/* sampleCodeModule.c */
#include "include/stdio.h"

char * v = (char*)0xB8000 + 79 * 2;

static int var1 = 0;
static int var2 = 0;


int main() {

	char greeting[6] = {'H', 'e', 'l', 'l', 'o', '\0'};

	clearScreen();

	printf(greeting);

	while(1) {

	}

	//Test if BSS is properly set up
	if (var1 == 0 && var2 == 0)
		return 0xDEADC0DE;

	return 0xDEADBEEF;
}
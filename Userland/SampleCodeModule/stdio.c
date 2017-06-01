#include "./types.h"

extern void int80(qword rdi, qword rsi, qword rdx, qword rcx, qword r8, qword r9);

/* Change this to accept multiple formats (like %i, %s, etc.) and abstract the int80 call */
void printf(const char* str) {
	int length = strlen(str);
	int80(1, 1, str, length, 0, 0);
}

void clearScreen() {
	int80(2, 1, 0, 0, 0, 0);
}

void printC(const char c) {
	int80(1, 0, &c, 1, 0, 0);
}

char getc() {
	char a[2];
	int80(3,0,a,2,0,0);
	if(a[0] == 0 ) return EOF;
	return a[0];
}
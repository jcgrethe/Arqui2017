#include "./types.h"

extern void int80(qword rdi, qword rsi, qword rdx, qword rcx, qword r8, qword r9);

/* Change this to accept multiple formats (like %i, %s, etc.) and abstract the int80 call */
void printf(const char* str) {
	int length = strlen(str);
	int80(1,1,str,length,0,0);
}

void clearScreen() {
	int80(2,1,0,0,0,0);
}
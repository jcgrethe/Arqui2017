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

void backspace(char c) {
	int80(1, 0 , &c, 1 ,0, 0);
}

void newLine(char c){
	int80(1, 0 , &c, 1 ,0, 0);
}


boolean strcmp(char* s1,char* s2){
	int x=0;
	boolean flag=true;
	while(s1[x]!=0 && s2[x]!=0 && flag==true){
		if(s1[x]!=s2[x]){
			flag=false;
		}
		x++;
	}
	if(flag==false)
		return flag;
	if(s1[x]==s2[x]){
		return true;
	}
	return false;
}
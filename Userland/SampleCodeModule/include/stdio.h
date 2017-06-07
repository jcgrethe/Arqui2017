#ifndef STDIO_H
#define STDIO_H

#include "../types.h"
void intostr(int num,char*a);
void printf(const char* str,int n,...);
void time(char* m,char* h,char* d,char* mo,char* y);
void clearScreen();
char getchar();
void backspace() ;
void newLine();
void putchar(char a);

#endif

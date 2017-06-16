#ifndef STDIO_H
#define STDIO_H

#include "../types.h"
void intostr(int num,char*a);
void printf(const char* str,...);
void time(char* m,char* h,char* d,char* mo,char* y);
void clearScreen();
char getchar();
void backspace() ;
void newLine();
void putchar(const char a);
int changeFontColor(char* color);
#endif

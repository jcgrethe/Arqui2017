#ifndef STDIO_H
#define STDIO_H

#include "../types.h"

void printf(const char* str);
void time(char* m,char* h,char* d,char* mo,char* y);
void clearScreen();
boolean strcmp(char* s1,char* s2);
char getc();
void backspace() ;
void newLine();

#endif

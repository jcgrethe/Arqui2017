#ifndef STDIO_H
#define STDIO_H

#include "../types.h"

void printf(const char* str);

void clearScreen();
boolean strcmp(char* s1,char* s2);
char getc();
void backspace(char c) ;
void newLine(char c);
#endif

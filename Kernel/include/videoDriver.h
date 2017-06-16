#ifndef VIDEO_DRIVER_H
#define VIDEO_DRIVER_H

#include <stdint.h>

void printString(const char * string);
void printChar(char character);
void newline();
void printDec(uint64_t value);
void printHex(uint64_t value);
void printBin(uint64_t value);
void printBase(uint64_t value, uint32_t base);
void clear();
void changeFontColor(char newColor);
void printPosition(signed char, signed char);
#endif

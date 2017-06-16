#include "include/types.h"
#include "include/videoDriver.h"


static dword uintToBase(qword value, char * buffer, dword base);

static char buffer[64] = { '0' };
static byte * const video = (byte*)0xB8000;
static byte * currentVideo = (byte*)0xB8000;
static byte fontColor = 0xF;
static const dword width = 80;
static const dword height = 25 ;
void printString(const char * string) {
	int i;

	for (i = 0; string[i] != 0; i++)
		printChar(string[i]);
}

void changeFontColor(char newColor) {
	fontColor = newColor;
}

void printChar(char c) {
	if (currentVideo >= (0xB8000 + 80*2*25)) {
		scrollDown();
		currentVideo = 0xB8000 + 80*2*24;
	}
	if(c=='\b') {
		backspace();
	} else if(c=='\n') {
		newline();
	} else {
		*currentVideo = c;
		currentVideo ++;
		*currentVideo = fontColor;
		currentVideo ++;
	}
}

static byte * mouse;
void printPosition(signed char x,signed char y) {
	for(int x=1;x<width*height*2-1;x+=2)
		video[x]=0X07;
	mouse=(video + x*2*80 + y*2+1);
	*mouse=0XAF;
	
}

void scrollDown() {
	int i;
	for (i = 0; i < 25; i++) {
		memcpy(video + i*80*2, video + (i + 1)*80*2, 80*2);
	}
}

void backspace() {
	if (currentVideo > 0xB8000) {
		currentVideo -= 2;
		printChar(' ');
		currentVideo -= 2;
	}
}

void newline() {
	do {
		printChar(' ');
	} while((qword)(currentVideo - video) % (width * 2) != 0);
}

void printDec(qword value) {
	printBase(value, 10);
}

void printHex(qword value) {
	printBase(value, 16);
}

void printBin(qword value) {
	printBase(value, 2);
}

void printBase(qword value, dword base) {
    uintToBase(value, buffer, base);
    printString(buffer);
}

void clear() {
	int i;

	for (i = 0; i < height * width; i++)
		video[i * 2] = ' ';
	currentVideo = video;
}

static dword uintToBase(qword value, char * buffer, dword base) {
	char *p = buffer;
	char *p1, *p2;
	dword digits = 0;

	//Calculate characters for each digit
	do	{
		dword remainder = value % base;
		*p++ = (remainder < 10) ? remainder + '0' : remainder + 'A' - 10;
		digits++;
	}	while (value /= base);

	// Terminate string in buffer.
	*p = 0;

	//Reverse string in buffer.
	p1 = buffer;
	p2 = p - 1;
	while (p1 < p2) {
		char tmp = *p1;
		*p1 = *p2;
		*p2 = tmp;
		p1++;
		p2--;
	}

	return digits;
}


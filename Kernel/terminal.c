#include "include/types.h"
#include "include/terminal.h"
#include "include/videoDriver.h"
#include "include/KeyboardDriver.h"
#include "include/mouseDriver.h"


static char *buffer[200];
void printMouse(signed char x,signed char y,boolean flag){
	printPosition(x,y,flag);
}

void cleanSelected(){
	cleanBack();
}

void copyToBuffer(){
	copyscreen(buffer);
}

void printCopy(){
	addToBuffer(buffer);
	buffer[0]=0;
}










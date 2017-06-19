#include "./types.h"
#include "include/shell.h"
#include "include/stdio.h"
#include "include/timeAndDate.h"
#include "include/string.h"
#include "include/blobsFront.h"
void initShell() {

  clearScreen();
  printf("Shell: ");
  newLine();
  char buffer[25*80];
  int index=0;
  char c;
  int state;
  boolean first=true;
  while(1) {
    if ((c = getchar()) != EOF) {
    	if(c=='\b'){
    		if(index!=0){
    			index--;
    			buffer[index]=0;
    			backspace();
    		}
    	}
      	else{
      		if(c=='\n'){
      			newLine();
      			buffer[index]=0;
      			state=callfunction(buffer);
				if(state!=0){
					printf("Unknown command.");
					newLine();
				}
				index=0;
				buffer[0]=0;
      		}else{
	      		buffer[index]=c;
	      		index++;
	      		buffer[index]=0;
	     		putchar(buffer[index-1]);	
	  		}	   
	  	}
		}
		if(first){
			backspace();
			index--;
			buffer[index]=0;
			first=false;
		}
	}
	
}

int callfunction(char* buffer) {
	int x=0;
	char function[10];
	//printf("%s",buffer);
	while(buffer[x]!=' ' && buffer[x]!=0) {
		function[x]=buffer[x];
		x++;
		if(x>9)
			return 1;
	}
	function[x]=0;
	if(strcmp(function, "echo")) {
		echo(buffer+x+1);
		return 0;
	}
	if(strcmp(function, "getTime")) {
		printTimeAndDate();
		return 0;
	}
	if(strcmp(function, "fontColor")) {
		return changeFontColor(buffer+x+1);
	}
	if(strcmp(function, "clear")) {
		 clearScreen();
		 return 0;
	}
	if(strcmp(function, "BlobsWar")) {
		clearScreen();
		 juego();
		 clearScreen();
		 printf("Shell:" );
		 return 0;
	}

	return 1;
}

void echo(char * buffer){
	printf(buffer);
	newLine();
}
#include "./types.h"
#include "include/stdio.h"
void initShell() {

  clearScreen();
  printf("Shell: ");
  printf("\n");
  char buffer[100];
  int index=0;
  char c;
  int state;
  while(1) {
    if ((c = getc()) != EOF) {
    	if(c=='\b'){
    		index--;
    		buffer[index]=0;
    		backspace(c);
    	}
      	else{
      		if(c=='\n'){
      			newLine(c);
      			buffer[index]=0;
      			state=callfunction(buffer);
				index=0;
				buffer[0]=0;
      		}else{
	      		buffer[index]=c;
	      		index++;
	      		buffer[index]=0;
	     		printf(&(buffer[index-1]) );
	      		
	  		}	   
	  	}
	 }
	}
}

int callfunction(char* buffer){
	int x=0;
	char function[10];
	while(buffer[x]!=' ' && buffer[x]!=0){
		function[x]=buffer[x];
		x++;
		if(x>9)
			return 1;
	}
	function[x]=0;
	if(strcmp(function,"echo")==true){
		printf(buffer+x);
		newLine('\n');

	}
		return 0;
}
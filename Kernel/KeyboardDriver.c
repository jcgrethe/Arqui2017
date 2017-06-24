#include <asciicode.h>
#include "include/KeyboardDriver.h"
#include "include/types.h"
#include <system_calls.h>
#define BUFFER_SIZE 2000

static byte buffer[BUFFER_SIZE];
static int index=0;
static int bufferindex=0;
static boolean ctrl=false;
static boolean caps=false;
static boolean shift=false;
static boolean alt=false;
static boolean rshift=false;
extern int read();

void keyboardHandler() {
	byte aux;
	byte key= read();
	 if (key == 0x1D || key==0X9D) {
        ctrl = !ctrl; 
        return;
    } else if(key==0x36 || key==0xB6){
        rshift=!rshift;
        return;
    }else if(key==0x2A || key==0XAA){
        shift=!shift;
        return;
    }else if(key==0x38 || key==0xB8){
        alt=!alt;
        return;
    }else if(key==0x3A){
        caps=!caps;
        return;
    }
    
    if(key&0X80)
    	return;

    if(ctrl || alt)
    	return;
    if(!caps && !shift && !rshift){
		key=ASCII_VALUE[key];
    }else{
		if(caps && !shift && !rshift){
			key=ASCII_VALUE[key];
			if(key>='a'&& key<='z')
				key=key-'a'+'A';
		}
		else{	
			if((shift|| rshift) && !caps)
				key=SHIFT_ASCII_VALUE[key];
			else{
					aux=ASCII_VALUE[key];
					if(aux<'a'|| aux>'z')
						key=SHIFT_ASCII_VALUE[key];
					else
						key=ASCII_VALUE[key];
			}
		}
	}
	buffer[bufferindex]=key;
	bufferindex=(bufferindex+1)%BUFFER_SIZE;
}

byte getBuffer(){
	if(index!=bufferindex){
		byte aux=buffer[index];
		index=(index+1)%BUFFER_SIZE;
		return aux;
	}
	return EOF;
}

void readAllBuffer(char* buff, int size){
    int i = 0;
    char c;

    while (i < size - 1 && (c = getBuffer()) != EOF) {
        buff[i] = (char) c;
        i++;
    }
    buff[i] = 0;
    
}

void addToBuffer(char *buffercopy){
	for(int x=0;buffercopy[x]!=0;x++){
		buffer[bufferindex]=buffercopy[x];
		bufferindex=(bufferindex+1)%BUFFER_SIZE;
	}
}
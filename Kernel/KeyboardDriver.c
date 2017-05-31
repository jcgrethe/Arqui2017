#include <asciicode.h>
#include <KeyboardDriver.h>
#include "include/types.h"
#define size 150
static byte buffer[size];
static char index=0;
static char bufferindex=0;
static boolean ctrl=false;
static boolean caps=false;
static boolean shift=false;
static boolean alt=false;
static boolean rshift=false;


void keyboardHandler() {
	byte aux;
	byte key= readk();
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
	bufferindex=(bufferindex+1)%size;	
}



byte getBuffer(){
	if(index<bufferindex){
		byte aux=buffer[index];
		index=(index+1)%size;
		return aux;
	}
	return EOF;
}


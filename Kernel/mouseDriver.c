#include "include/types.h"
#include "include/mouseDriver.h"
#include <system_calls.h>
#include "include/videoDriver.h"
#include "include/RegisterHandler.h"

//info: http://houbysoft.com/download/ps2mouse.html


extern dword read();

void set_up_mouse(){

//espera a poder escribirle al mouse
    mWait(1);
    outIO(0x64,0xA8);

    mWait(1);
    outIO(0x64,0x20);
//espera para leer del mouse
	mWait(0);
	char status = (inIO(0x60) | 2);
	//status = (status & 0xEF);

	mWait(1);
	outIO(0x64, 0x60);

	mWait(1);
	outIO(0x60, status);

	mWrite(0xF6);
	mRead();

	mWrite(0xF4);
	mRead();
	
}

byte mRead(){
	//Espera a poder leer
	mWait(0);
	return inIO(0x60);
}

void mWrite(char command){
	//Espera para poder mandar un comando
	mWait(1);
	//Le avisa que estamos por enviar un comando
	outIO(0x64, 0xD4);
	//Esperamos para poder escribir el comando
	mWait(1);
	//Escribimos el comando
	outIO(0x60, command);
}

void mWait(int t){
	unsigned int time_out = 100000;

	if(t == 0){
		while( time_out-- ){
			if((inIO(0x64) & 1) == 1)
				return;
		}
    return;

  }else{
	  while(time_out--){
		  if((inIO(0x64) & 2)==0)
		  	return;
	}
    return;

  }

}

static uint8_t mouse_x = 0;
static uint8_t mouse_y = 0;
static int cycle = 0;
static char mouseByte[3];
void mouseHandler(){
    
    
   if(!(inIO(0x64)& 0x20))
   		return;
    switch(cycle){
    	case 0:
	  		//ncPrintChar('b');
	  		mouseByte[0] = mRead();
	  		//ncPrintChar('c');
	  		cycle++;
	  		if(mouseByte[0] & 0x80 || mouseByte[0] & 0x40) {
	  			//ncPrintChar('d');
	  			cycle = 0;
	  		}
		break;
		case 1:
		  	//ncPrintChar('e');
		  	mouseByte[1] = mRead();
		    //ncPrintChar('f');
		    cycle++;
			break;
		case 2:
		  	//ncPrintChar('g');
		  	mouseByte[2] = mRead();
		  	//ncPrintChar('h');
		  	cycle = 0;
		  	uint8_t mouse_x_aux = mouse_x + mouseByte[1];
		  	//ncPrintChar('i');
		  	uint8_t mouse_y_aux = mouse_y - mouseByte[2];
		  	//ncPrintChar('j');
		  	if((mouse_x_aux >= 0 && mouse_x_aux <= 79) && (mouse_y_aux >= 0 && mouse_y_aux <= 24)) {
		  		//ncPrintChar('k');
		  		mouse_x += mouseByte[1];
		  		//ncPrintChar('l');
		  		mouse_y -= mouseByte[2];
		  		//ncPrintChar('m');
		  		//printDec(mouse_x);
		  		//newline();
		  		//printDec(mouse_y);
				//newline();
				printPosition(mouse_x,mouse_y);

			}
			//ncPrintChar('n');
			if(mouseByte[0] & 0x01)
				//ncPrint("Left Button");
			if(mouseByte[0] & 0x02)
				//ncPrint("Right Button");
	  	break;
    }
    
}
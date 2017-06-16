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

static signed char mouse_x = 0;
static signed char mouse_y = 0;

static int cycle = 0;
static unsigned char mouseByte[3] = {0};

signed char mouse_x_acum = 0;
signed char mouse_y_acum = 0;

void mouseHandler() {
    
	mouseByte[cycle++] = mRead();

	if(cycle == 3) {
		cycle = 0;

		if(!(inIO(0x64) & 0x20) || mouseByte[0] & 0x80 || mouseByte[0] & 0x40) {
			return;
		}
				
		mouse_x_acum += (signed char)mouseByte[1];
		mouse_y_acum += (signed char)mouseByte[2];
		
		/*
		* Checkeo si el acumulador en X del mouse llego hasta -20
		* para hacer un unico movimiento hacia la izquierda
		*/
		if (mouse_x_acum <= -20) {
			if(mouse_x < 24) {
				mouse_x += 1;
			}
			mouse_x_acum = 0;
		} else if (mouse_x_acum >= 20) {
			if(mouse_x > 0) {
				mouse_x -= 1;
			}
			mouse_x_acum = 0;
		}
		
		if (mouse_y_acum <= -20) {
			if(mouse_y > 0) {
				mouse_y -= 1;
			}
			mouse_y_acum = 0;
		} else if (mouse_y_acum >= 20) {
			if(mouse_y < 79) {
				mouse_y += 1;
			}
			mouse_y_acum = 0;
		}

		printPosition(mouse_x, mouse_y);

		if(mouseByte[0] & 0x01) {
			//printString("Left Button");
		}

		if(mouseByte[0] & 0x02) {
			//printString("Right Button");
		}
	}    
}

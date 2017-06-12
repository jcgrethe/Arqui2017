#include "include/types.h"
#include "include/mouseDriver.h"
#include <system_calls.h>
#include "include/videoDriver.h"
#include "include/RegisterHandler.h"

//info: http://houbysoft.com/download/ps2mouse.html

static byte x = 10;
static byte y = 15;
extern dword read();

void set_up_mouse(){

//espera a poder escribirle al mouse
    mWait(1);
    outIO(0x64,0xA8);

    mWait(1);
    outIO(0x64,0x20);
//espera para leer del mouse
	mWait(0);
	byte status = (inIO(0x60) | 2);
	status = (status & 0xEF);

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

void mWrite(byte command){
	//Espera para poder mandar un comando
	mWait(1);
	//Le avisa que estamos por enviar un comando
	outIO(0x64, 0xD4);
	//Esperamos para poder escribir el comando
	mWait(1);
	//Escribimos el comando
	outIO(0x60, command);
}

void mWait(byte t){
	dword time_out = 100000;

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

void mouseHandler(){
    
    static byte cycle = 0;
    static char mouse_bytes[3];
    mouse_bytes[cycle++] = read();

    if (cycle == 3) { // if we have all the 3 bytes...
        cycle = 0; // reset the counter
    // do what you wish with the bytes, this is just a sample
		if ((mouse_bytes[0] & 0x80) || (mouse_bytes[0] & 0x40))
		    return; // the mouse only sends information about overflowing, do not care about it and return
		if (!(mouse_bytes[0] & 0x20)){
		   // printString("delta-y es negativo");
		    y += mouse_bytes[2]/30;
		}else{
		   // printString("delta-y es positivo");
		    y -= mouse_bytes[2]/30;
		}
		if (!(mouse_bytes[0] & 0x10)){
		   // printString("delta-x es negativo");
		    x += mouse_bytes[1]/30;
		}else{
		   // printString("delta-x es positivo");
		    x -= mouse_bytes[1]/30;
		}
		printPosition(x,y);
		if (mouse_bytes[0] & 0x4);
		   // printString("Middle button is pressed!n");
		if (mouse_bytes[0] & 0x2);
		   // printString("Right button is pressed!n");
		if (mouse_bytes[0] & 0x1);
		   // printString("Left button is pressed!n");

    // do what you want here, just replace the puts's to execute an action for each button
    // to use the coordinate data, use mouse_bytes[1] for delta-x, and mouse_bytes[2] for delta-y
  }
}
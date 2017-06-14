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
	unsigned char status = (inIO(0x60) | 2);
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

unsigned char mRead(){
	//Espera a poder leer
	mWait(0);
	return inIO(0x60);
}

void mWrite(unsigned char command){
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

static int cycle=0;
static char mouseByte[3];
void mouseHandler(){
   
   
	   mouseByte[cycle] = mRead();

	    if (cycle == 0) {
	        // If Y or X overflows are set, I discard packet.
	          if(mouseByte[0] & 0x80 || mouseByte[0] & 0x40) {
	             // cycle = -1;
	        }
	    } else if (cycle == 2) {
	          cycle = -1;
	       // mouseByte[1]=mouseByte[1]/10;
	       // mouseByte[2]=mouseByte[2]/10;
	        printPosition(mouseByte[1],mouseByte[2]);

	        if(mouseByte[0] & 0x01) {
	            //print("Left Button");
	        }
	        if(mouseByte[0] & 0x02) {
	            //print("Right Button");
	        }
	    }
	    cycle++;
 	
}
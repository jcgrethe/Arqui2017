#include "include/types.h"
#include "include/mouseDriver.h"
#include <system_calls.h>
#include "include/videoDriver.h"
#include "include/RegisterHandler.h"
#include "include/terminal.h"

//info: http://houbysoft.com/download/ps2mouse.html

#define PACKETS_IN_PIPE 1024
#define DISCARD_POINT 32



#define MOUSE_PORT   0x60
#define MOUSE_STATUS 0x64
#define MOUSE_ABIT   0x02
#define MOUSE_BBIT   0x01
#define MOUSE_WRITE  0xD4
#define MOUSE_F_BIT  0x20
#define MOUSE_V_BIT  0x08
#define MOUSE_IRQ 12

extern dword read();

void set_up_mouse(){

	int8_t status;
	
	mWait(1);
	outIO(MOUSE_STATUS, 0xA8);
	mWait(1);
	outIO(MOUSE_STATUS, 0x20);
	mWait(0);
	status = inIO(0x60) | 2;
	mWait(1);
	outIO(MOUSE_STATUS, 0x60);
	mWait(1);
	outIO(MOUSE_PORT, status);
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

static uint8_t mouse_cycle = 0;
static int8_t  mouse_byte[3];
static int8_t x=2;
static int8_t y=5;
static boolean left=false;
//https://github.com/stevej/osdev/blob/master/kernel/devices/mouse.c
int8_t auxx;
int8_t auxy;
void mouseHandler() {
    
	int8_t status = inIO(MOUSE_STATUS);
	while (status & MOUSE_BBIT) {
		int8_t mouse_in = inIO(MOUSE_PORT);
		if (status & MOUSE_F_BIT) {
			switch (mouse_cycle) {
				case 0:
					mouse_byte[0] = mouse_in;
					if (!(mouse_in & MOUSE_V_BIT)) return;
					++mouse_cycle;
					break;
				case 1:
					mouse_byte[1] = mouse_in;
					++mouse_cycle;
					break;
				case 2:
					mouse_byte[2] = mouse_in;
					mouse_cycle = 0;
					/* We now have a full mouse packet ready to use */
					if (mouse_byte[0] & 0x80 || mouse_byte[0] & 0x40) {
						/* x/y overflow? bad packet! */
						break;
					}
					if (mouse_byte[0] & 0x04) {
					}
					
					auxx=0;
					auxy=0;
					if (mouse_byte[0] & 0x01) {
						//printString(" left");
						if(left==false)
							cleanSelected();
						left=true;
					}else{
						if(left==true)
							copyToBuffer();
						left=false;
					}
					if (mouse_byte[0] & 0x02) {
						//habria que mandarlo al buffer de teclado
							printCopy();
					}
					auxx=x+mouse_byte[1];
					auxy=y-mouse_byte[2];
					if(auxy>=0 && auxx>=0 && auxy<25 && auxx<80){
						x+=mouse_byte[1];
						y-=mouse_byte[2];
						printMouse(y,x,left);
					}
				}
			}
		}
		status = inIO(MOUSE_STATUS);
	}

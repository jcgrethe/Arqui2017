//interruptions.c
#include <interruptions.h>
#include "include/types.h"

#pragma pack(push)
#pragma pack(1)

typedef struct { 
	word offset_l; //bit 0..15
	word selector;
	byte zero_l;
	byte attrs;
	word offset_m; //16..31
	dword offset_h; //32..63
	dword zero_h;
} IDTEntry_t;

#pragma pack(pop)

void tickHandler() {
	// video[i++] = i;	
}



typedef void (*handler_t)(void);

handler_t handlers[] = {tickHandler, keyboardHandler, mouseHandler};

void irqDispatcher(int irq) {
	handlers[irq]();
}

static IDTEntry_t* IDT = (IDTEntry_t*) 0x0;

void interruption_set_handler(int index, qword handler) {
	IDT[index].offset_l = (word) handler & 0xFFFF;
	IDT[index].offset_m = (word) (handler >> 16) & 0xFFFF;
	IDT[index].offset_h = (dword) (handler >> 32) & 0xFFFFFFFF;
	
	IDT[index].selector = 0x08;
	IDT[index].zero_l = 0;
	
	IDT[index].attrs = 0x8E;
	IDT[index].zero_h = 0;	
	
}

void set_up_IDT() {
	cli();

	interruption_set_handler(0x20, (qword) irq0Handler);
	interruption_set_handler(0x21, (qword) irq1Handler);
	interruption_set_handler(0x2C, (qword) irq2Handler);

	setPicMaster(0xF8);
	setPicSlave((char*)0xEF);
	
	sti();
}


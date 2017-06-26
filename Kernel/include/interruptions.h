#ifndef _INTERRUPTIONS_H_
#define _INTERRUPTIONS_H_

#include "types.h"

void sti();
void cli();
void irq0Handler();
void irq1Handler();
void irq2Handler();
void setPicMaster(word);
extern void setPicSlave(char*);
void tickHandler();
void keyboardHandler();
void mouseHandler();
void irqDispatcher(int irq);
void set_up_IDT();
void interruption_set_handler(int index, qword handler);

void irq80Handler(void);

#endif

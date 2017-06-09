#ifndef _INTERRUPTIONS_H_
#define _INTERRUPTIONS_H_

#include "types.h"

void sti();
void cli();
void irq0Handler();
void irq1Handler();
void irq2Handler();
void setPicMaster(word);

void tickHandler();
void keyboardHandler();
void mouseHandler();
void irqDispatcher(int irq);

void interruption_set_handler(int index, qword handler);

void irq80Handler(void);

#endif

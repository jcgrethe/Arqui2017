#ifndef MOUSE_DRIVER_H
#define MOUSE_DRIVER_H

void set_up_mouse();
unsigned char mRead();
void mWrite(unsigned char);
void mWait(int);
void mouseHandler();

#endif

#ifndef MOUSE_DRIVER_H
#define MOUSE_DRIVER_H

void set_up_mouse();
byte mRead();
void mWrite(char);
void mWait(int);
void mouseHandler();

#endif
